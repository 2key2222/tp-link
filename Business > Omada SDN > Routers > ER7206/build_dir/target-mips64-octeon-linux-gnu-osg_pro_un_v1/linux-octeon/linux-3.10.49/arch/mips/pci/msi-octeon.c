/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2005-2012 Cavium Inc.
 */
#include <linux/interrupt.h>
#include <linux/spinlock.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/cpu.h>
#include <linux/msi.h>

#include <asm/octeon/octeon.h>
#include <asm/octeon/cvmx-npi-defs.h>
#include <asm/octeon/cvmx-pci-defs.h>
#include <asm/octeon/cvmx-npei-defs.h>
#include <asm/octeon/cvmx-pexp-defs.h>
#include <asm/octeon/cvmx-sli-defs.h>
#include <asm/octeon/cvmx-ciu2-defs.h>
#include <asm/octeon/pci-octeon.h>

/*
 * Each bit in msi_free_irq_bitmask represents a MSI interrupt that is
 * in use.
 */
static u64 msi_free_irq_bitmask[4];

/*
 * Each bit in msi_multiple_irq_bitmask tells that the device using
 * this bit in msi_free_irq_bitmask is also using the next bit. This
 * is used so we can disable all of the MSI interrupts when a device
 * uses multiple.
 */
static u64 msi_multiple_irq_bitmask[4];

/*
 * This lock controls updates to msi_free_irq_bitmask and
 * msi_multiple_irq_bitmask.
 */
static DEFINE_SPINLOCK(msi_free_irq_bitmask_lock);

/*
 * Number of MSI IRQs used. This variable is set up in
 * the module init time.
 */
static int msi_irq_size;

/**
 * Called when a driver request MSI interrupts instead of the
 * legacy INT A-D. This routine will allocate multiple interrupts
 * for MSI devices that support them. A device can override this by
 * programming the MSI control bits [6:4] before calling
 * pci_enable_msi().
 *
 * @dev:    Device requesting MSI interrupts
 * @desc:   MSI descriptor
 *
 * Returns 0 on success.
 */
int arch_setup_msi_irq(struct pci_dev *dev, struct msi_desc *desc)
{
	struct msi_msg msg;
	u16 control;
	int configured_private_bits;
	int request_private_bits;
	int irq = 0;
	int irq_step;
	u64 search_mask;
	int index;

	/*
	 * Read the MSI config to figure out how many IRQs this device
	 * wants.  Most devices only want 1, which will give
	 * configured_private_bits and request_private_bits equal 0.
	 */
	pci_read_config_word(dev, desc->msi_attrib.pos + PCI_MSI_FLAGS,
			     &control);

	/*
	 * If the number of private bits has been configured then use
	 * that value instead of the requested number. This gives the
	 * driver the chance to override the number of interrupts
	 * before calling pci_enable_msi().
	 */
	configured_private_bits = (control & PCI_MSI_FLAGS_QSIZE) >> 4;
	if (configured_private_bits == 0) {
		/* Nothing is configured, so use the hardware requested size */
		request_private_bits = (control & PCI_MSI_FLAGS_QMASK) >> 1;
	} else {
		/*
		 * Use the number of configured bits, assuming the
		 * driver wanted to override the hardware request
		 * value.
		 */
		request_private_bits = configured_private_bits;
	}

	/*
	 * The PCI 2.3 spec mandates that there are at most 32
	 * interrupts. If this device asks for more, only give it one.
	 */
	if (request_private_bits > 5)
		request_private_bits = 0;

try_only_one:
	/*
	 * The IRQs have to be aligned on a power of two based on the
	 * number being requested.
	 */
	irq_step = 1 << request_private_bits;

	/* Mask with one bit for each IRQ */
	search_mask = (1ull << irq_step) - 1;

	/*
	 * We're going to search msi_free_irq_bitmask_lock for zero
	 * bits. This represents an MSI interrupt number that isn't in
	 * use.
	 */
	spin_lock(&msi_free_irq_bitmask_lock);
	for (index = 0; index < msi_irq_size/64; index++) {
		for (irq = 0; irq < 64; irq += irq_step) {
			if ((msi_free_irq_bitmask[index] & (search_mask << irq)) == 0) {
				msi_free_irq_bitmask[index] |= search_mask << irq;
				msi_multiple_irq_bitmask[index] |= (search_mask >> 1) << irq;
				goto msi_irq_allocated;
			}
		}
	}
msi_irq_allocated:
	spin_unlock(&msi_free_irq_bitmask_lock);

	/* Make sure the search for available interrupts didn't fail */
	if (irq >= 64) {
		if (request_private_bits) {
			pr_err("arch_setup_msi_irq: Unable to find %d free interrupts, trying just one",
			       1 << request_private_bits);
			request_private_bits = 0;
			goto try_only_one;
		} else
			panic("arch_setup_msi_irq: Unable to find a free MSI interrupt");
	}

	/* MSI interrupts start at logical IRQ OCTEON_IRQ_MSI_BIT0 */
	irq += index*64;
	msg.data = irq;
	irq += OCTEON_IRQ_MSI_BIT0;

	switch (octeon_dma_bar_type) {
	case OCTEON_DMA_BAR_TYPE_SMALL:
		/* When not using big bar, Bar 0 is based at 128MB */
		msg.address_lo =
			((128ul << 20) + CVMX_PCI_MSI_RCV) & 0xffffffff;
		msg.address_hi = ((128ul << 20) + CVMX_PCI_MSI_RCV) >> 32;
		break;
	case OCTEON_DMA_BAR_TYPE_BIG:
		/* When using big bar, Bar 0 is based at 0 */
		msg.address_lo = (0 + CVMX_PCI_MSI_RCV) & 0xffffffff;
		msg.address_hi = (0 + CVMX_PCI_MSI_RCV) >> 32;
		break;
	case OCTEON_DMA_BAR_TYPE_PCIE:
		/* When using PCIe, Bar 0 is based at 0 */
		/* FIXME CVMX_NPEI_MSI_RCV* other than 0? */
		msg.address_lo = (0 + CVMX_NPEI_PCIE_MSI_RCV) & 0xffffffff;
		msg.address_hi = (0 + CVMX_NPEI_PCIE_MSI_RCV) >> 32;
		break;
	case OCTEON_DMA_BAR_TYPE_PCIE2:
		/* When using PCIe2, Bar 0 is based at 0 */
		msg.address_lo = (0 + CVMX_SLI_PCIE_MSI_RCV) & 0xffffffff;
		msg.address_hi = (0 + CVMX_SLI_PCIE_MSI_RCV) >> 32;
		break;
	default:
		panic("arch_setup_msi_irq: Invalid octeon_dma_bar_type");
	}

	/* Update the number of IRQs the device has available to it */
	control &= ~PCI_MSI_FLAGS_QSIZE;
	control |= request_private_bits << 4;
	pci_write_config_word(dev, desc->msi_attrib.pos + PCI_MSI_FLAGS,
			      control);

	irq_set_msi_desc(irq, desc);
	write_msi_msg(irq, &msg);
	return 0;
}

int arch_setup_msi_irqs(struct pci_dev *dev, int nvec, int type)
{
	struct msi_desc *entry;
	int ret;

	/*
	 * MSI-X is not supported.
	 */
	if (type == PCI_CAP_ID_MSIX)
		return -EINVAL;

	/*
	 * If an architecture wants to support multiple MSI, it needs to
	 * override arch_setup_msi_irqs()
	 */
	if (type == PCI_CAP_ID_MSI && nvec > 1)
		return 1;

	list_for_each_entry(entry, &dev->msi_list, list) {
		ret = arch_setup_msi_irq(dev, entry);
		if (ret < 0)
			return ret;
		if (ret > 0)
			return -ENOSPC;
	}

	return 0;
}

/**
 * Called when a device no longer needs its MSI interrupts. All
 * MSI interrupts for the device are freed.
 *
 * @irq:    The devices first irq number. There may be multple in sequence.
 */
void arch_teardown_msi_irq(unsigned int irq)
{
	int number_irqs;
	u64 bitmask;
	int index = 0;
	int irq0;

	if ((irq < OCTEON_IRQ_MSI_BIT0)
		|| (irq > msi_irq_size + OCTEON_IRQ_MSI_BIT0 - 1))
		panic("arch_teardown_msi_irq: Attempted to teardown illegal MSI interrupt (%d)",
		      irq);

	irq -= OCTEON_IRQ_MSI_BIT0;
	index = irq / 64;
	irq0 = irq % 64;
	/*
	 * Count the number of IRQs we need to free by looking at the
	 * msi_multiple_irq_bitmask. Each bit set means that the next
	 * IRQ is also owned by this device.
	 */
	number_irqs = 0;
	while ((irq0 + number_irqs < 64) &&
	       (msi_multiple_irq_bitmask[index]
		& (1ull << (irq0 + number_irqs))))
		number_irqs++;
	number_irqs++;
	/* Mask with one bit for each IRQ */
	bitmask = (1ull << number_irqs) - 1;
	/* Shift the mask to the correct bit location */
	bitmask <<= irq0;
	if ((msi_free_irq_bitmask[index] & bitmask) != bitmask)
		panic("arch_teardown_msi_irq: Attempted to teardown MSI interrupt (%d) not in use",
		      irq);

	/* Checks are done, update the in use bitmask */
	spin_lock(&msi_free_irq_bitmask_lock);
	msi_free_irq_bitmask[index] &= ~bitmask;
	msi_multiple_irq_bitmask[index] &= ~bitmask;
	spin_unlock(&msi_free_irq_bitmask_lock);
}

static DEFINE_RAW_SPINLOCK(octeon_irq_msi_lock);

static u64 msi_rcv_reg[4];
static u64 msi_ena_reg[4];

static int (*octeon_irq_msi_to_irq)(int);
static int (*octeon_irq_irq_to_msi)(int);

static int octeon_irq_msi_to_irq_linear(int msi)
{
	return msi + OCTEON_IRQ_MSI_BIT0;
}

static int octeon_irq_irq_to_msi_linear(int irq)
{
	return irq - OCTEON_IRQ_MSI_BIT0;
}

static int octeon_irq_msi_to_irq_scatter(int msi)
{
	return (((msi >> 6) & 0x3) | ((msi << 2) & 0xfc)) + OCTEON_IRQ_MSI_BIT0;
}

static int octeon_irq_irq_to_msi_scatter(int irq)
{
	int t = irq - OCTEON_IRQ_MSI_BIT0;
	return ((t << 6) & 0xc0) | ((t >> 2) & 0x3f);
}

#ifdef CONFIG_SMP

static atomic_t affinity_in_progress[4] = {
	ATOMIC_INIT(1),
	ATOMIC_INIT(1),
	ATOMIC_INIT(1),
	ATOMIC_INIT(1)};

static int octeon_irq_msi_set_affinity_pcie(struct irq_data *data,
					    const struct cpumask *dest,
					    bool force)
{
	int msi = octeon_irq_irq_to_msi(data->irq);
	int index = msi >> 6;
	int bit;
	int r;

	/*
	 * If we are in the middle of updating the set, the first call
	 * takes care of everything, do nothing successfully.
	 */
	if (atomic_sub_if_positive(1, affinity_in_progress + index) < 0)
		return 0;

	r = irq_set_affinity(OCTEON_IRQ_PCI_MSI0 + index, dest);

	for (bit = 0; bit < 64; bit++) {
		int partner = octeon_irq_msi_to_irq(64 * index + bit);
		if (partner != data->irq)
			irq_set_affinity(partner, dest);
	}
	atomic_add(1, affinity_in_progress + index);
	return r;
}

static int octeon_irq_msi_set_affinity_pci(struct irq_data *data,
					   const struct cpumask *dest,
					   bool force)
{
	int msi = octeon_irq_irq_to_msi(data->irq);
	int index = msi >> 4;
	int bit;
	int r;

	/*
	 * If we are in the middle of updating the set, the first call
	 * takes care of everything, do nothing successfully.
	 */
	if (atomic_sub_if_positive(1, affinity_in_progress + index) < 0)
		return 0;

	r = irq_set_affinity(OCTEON_IRQ_PCI_MSI0 + index, dest);

	for (bit = 0; bit < 16; bit++) {
		int partner = octeon_irq_msi_to_irq(16 * index + bit);
		if (partner != data->irq)
			irq_set_affinity(partner, dest);
	}
	atomic_add(1, affinity_in_progress + index);
	return r;
}
#endif /* CONFIG_SMP */

static void octeon_irq_msi_enable_pcie(struct irq_data *data)
{
	u64 en;
	unsigned long flags;
	int msi_number = octeon_irq_irq_to_msi(data->irq);
	int irq_index = msi_number >> 6;
	int irq_bit = msi_number & 0x3f;

	raw_spin_lock_irqsave(&octeon_irq_msi_lock, flags);
	en = cvmx_read_csr(msi_ena_reg[irq_index]);
	en |= 1ull << irq_bit;
	cvmx_write_csr(msi_ena_reg[irq_index], en);
	cvmx_read_csr(msi_ena_reg[irq_index]);
	raw_spin_unlock_irqrestore(&octeon_irq_msi_lock, flags);
}

static void octeon_irq_msi_disable_pcie(struct irq_data *data)
{
	u64 en;
	unsigned long flags;
	int msi_number = octeon_irq_irq_to_msi(data->irq);
	int irq_index = msi_number >> 6;
	int irq_bit = msi_number & 0x3f;

	raw_spin_lock_irqsave(&octeon_irq_msi_lock, flags);
	en = cvmx_read_csr(msi_ena_reg[irq_index]);
	en &= ~(1ull << irq_bit);
	cvmx_write_csr(msi_ena_reg[irq_index], en);
	cvmx_read_csr(msi_ena_reg[irq_index]);
	raw_spin_unlock_irqrestore(&octeon_irq_msi_lock, flags);
}

static struct irq_chip octeon_irq_chip_msi_pcie = {
	.name = "MSI",
	.irq_enable = octeon_irq_msi_enable_pcie,
	.irq_disable = octeon_irq_msi_disable_pcie,
#ifdef CONFIG_SMP
	.irq_set_affinity = octeon_irq_msi_set_affinity_pcie,
#endif
};

static void octeon_irq_msi_enable_pci(struct irq_data *data)
{
	/*
	 * Octeon PCI doesn't have the ability to mask/unmask MSI
	 * interrupts individually. Instead of masking/unmasking them
	 * in groups of 16, we simple assume MSI devices are well
	 * behaved. MSI interrupts are always enable and the ACK is
	 * assumed to be enough
	 */
}

static void octeon_irq_msi_disable_pci(struct irq_data *data)
{
	/* See comment in enable */
}

static struct irq_chip octeon_irq_chip_msi_pci = {
	.name = "MSI",
	.irq_enable = octeon_irq_msi_enable_pci,
	.irq_disable = octeon_irq_msi_disable_pci,
#ifdef CONFIG_SMP
	.irq_set_affinity = octeon_irq_msi_set_affinity_pci,
#endif
};

/*
 * Called by the interrupt handling code when an MSI interrupt
 * occurs.
 */
static irqreturn_t __octeon_msi_do_interrupt(int index, u64 msi_bits)
{
	int irq;
	int bit;

	bit = fls64(msi_bits);
	if (bit) {
		bit--;
		/* Acknowledge it first. */
		cvmx_write_csr(msi_rcv_reg[index], 1ull << bit);

		irq = octeon_irq_msi_to_irq(bit + 64 * index);

		generic_handle_irq(irq);
		return IRQ_HANDLED;
	}
	return IRQ_NONE;
}

#define OCTEON_MSI_INT_HANDLER_X(x)					\
static irqreturn_t octeon_msi_interrupt##x(int cpl, void *dev_id)	\
{									\
	u64 msi_bits = cvmx_read_csr(msi_rcv_reg[(x)]);			\
	return __octeon_msi_do_interrupt((x), msi_bits);		\
}

/*
 * Create octeon_msi_interrupt{0-3} function body
 */
OCTEON_MSI_INT_HANDLER_X(0);
OCTEON_MSI_INT_HANDLER_X(1);
OCTEON_MSI_INT_HANDLER_X(2);
OCTEON_MSI_INT_HANDLER_X(3);

#if 0
static void octeon_msi_ciu2_enable_on_cpu(unsigned int irq, int cpu)
{
	int core;
	int msi = irq - OCTEON_IRQ_MSI_BIT0;
	union cvmx_ciu2_msi_selx sel;

	core = octeon_coreid_for_cpu(cpu);

	sel.u64 = 0;
	sel.s.pp_num = core;
	sel.s.ip_num = 2; /* IP4 */
	sel.s.en = 1;
	cvmx_write_csr(CVMX_CIU2_MSI_SELX(msi), sel.u64);
	/* Read back some CSR for write to complete. */
	cvmx_read_csr(CVMX_CIU2_SUM_PPX_IP2(core));
}

static void octeon_msi_ciu2_enable(struct irq_data *data)
{
	int cpu;

#ifdef CONFIG_SMP
	cpu = cpumask_first(data->affinity);
#else
	cpu = 0;
#endif
	octeon_msi_ciu2_enable_on_cpu(data->irq, cpu);
}

static void octeon_msi_ciu2_disable(struct irq_data *data)
{
	int msi = data->irq - OCTEON_IRQ_MSI_BIT0;
	union cvmx_ciu2_msi_selx sel;

	sel.u64 = cvmx_read_csr(CVMX_CIU2_MSI_SELX(msi));
	sel.s.en = 0;
	cvmx_write_csr(CVMX_CIU2_MSI_SELX(msi), sel.u64);
	cvmx_read_csr(CVMX_CIU2_INTR_CIU_READY);
}

static void octeon_msi_ciu2_ack(struct irq_data *data)
{
	int msi = data->irq - OCTEON_IRQ_MSI_BIT0;

	cvmx_write_csr(CVMX_CIU2_MSI_RCVX(msi), 0);
	cvmx_read_csr(CVMX_CIU2_INTR_CIU_READY);
}

#ifdef CONFIG_SMP
static int octeon_msi_ciu2_set_affinity(struct irq_data *data,
					const struct cpumask *dest,
					bool force)
{
	int cpu = cpumask_first(dest);

	/*
	 * For CIU2-MSI, we will allow only single CPU affinity.
	 * This .
	 */
	if (cpumask_weight(dest) != 1)
		return -EINVAL;

	octeon_msi_ciu2_enable_on_cpu(data->irq, cpu);

	return 0;
}
#endif

static struct irq_chip octeon_msi_chip_ciu2 = {
	.name = "CIU2-MSI",
	.irq_enable = octeon_msi_ciu2_enable,
	.irq_disable = octeon_msi_ciu2_disable,
	.irq_ack = octeon_msi_ciu2_ack,
	.irq_mask = octeon_msi_ciu2_disable,
	.irq_unmask = octeon_msi_ciu2_enable,
#ifdef CONFIG_SMP
	.irq_set_affinity = octeon_msi_ciu2_set_affinity,
	.irq_cpu_offline = octeon_irq_cpu_offline_ciu,
#endif
};

static void octeon_msi_ip4(void)
{
	union cvmx_ciu2_msired_ppx_ip4 msired;
	int core = cvmx_get_core_num();

	msired.u64 = cvmx_read_csr(CVMX_CIU2_MSIRED_PPX_IP4(core));

	if (msired.s.intr)
		do_IRQ(msired.s.msi_num + OCTEON_IRQ_MSI_BIT0);
	else
		spurious_interrupt();
}

static int octeon_msi_cpu_callback(struct notifier_block *nfb,
				   unsigned long action, void *hcpu)
{
	unsigned int cpu = (unsigned long)hcpu;

	switch (action) {
	case CPU_DOWN_PREPARE:
		cvmx_write_csr(CVMX_CIU2_EN_PPX_IP4_IO_W1C(cpu_logical_map(cpu)),
			       1<<12);
		break;
	case CPU_ONLINE:
	case CPU_DOWN_FAILED:
		cvmx_write_csr(CVMX_CIU2_EN_PPX_IP4_IO_W1S(cpu_logical_map(cpu)),
			       1<<12);
		break;
	default:
		break;
	}
	return NOTIFY_OK;
}

static struct notifier_block octeon_msi_cpu_notifier = {
	.notifier_call = octeon_msi_cpu_callback,
};

static int __init octeon_msi_68XX_init(void)
{
	int i;
	int cpu;

	/* Disable legacy handling. */
	cvmx_write_csr(CVMX_PEXP_SLI_MSI_ENB0, 0);
	cvmx_write_csr(CVMX_PEXP_SLI_MSI_ENB1, 0);
	cvmx_write_csr(CVMX_PEXP_SLI_MSI_ENB2, 0);
	cvmx_write_csr(CVMX_PEXP_SLI_MSI_ENB3, 0);

	/* Disable CIU2_MSI */
	for (i = 0; i < 256; i++)
		cvmx_write_csr(CVMX_CIU2_MSI_SELX(i), 0);

	for (i = OCTEON_IRQ_MSI_BIT0; i <= OCTEON_IRQ_MSI_LAST; i++)
		irq_set_chip_and_handler(i, &octeon_msi_chip_ciu2, handle_edge_irq);

	octeon_irq_set_ip4_handler(octeon_msi_ip4);
	/* Enable MSIRED interrupt */
#ifdef CONFIG_SMP
	for_each_online_cpu(cpu)
		cvmx_write_csr(CVMX_CIU2_EN_PPX_IP4_IO_W1S(cpu_logical_map(cpu)),
			       1<<12);
#else
	cvmx_write_csr(CVMX_CIU2_EN_PPX_IP4_IO_W1S(cvmx_get_core_num()),
			       1<<12);
#endif
	cvmx_read_csr(CVMX_CIU2_SUM_PPX_IP2(cvmx_get_core_num()));

	register_hotcpu_notifier(&octeon_msi_cpu_notifier);

	msi_irq_size = 256;
	return 0;
}
#endif /* 0 */

/*
 * Initializes the MSI interrupt handling code
 */
int __init octeon_msi_initialize(void)
{
	int irq;
	struct irq_chip *msi;
	u64 msi_map_reg;

	if (OCTEON_IS_MODEL(OCTEON_CN78XX))
		return 0;
#if 0
	if (OCTEON_IS_MODEL(OCTEON_CN68XX) && !OCTEON_IS_MODEL(OCTEON_CN68XX_PASS1_X))
		return octeon_msi_68XX_init();
#endif

	if (octeon_dma_bar_type == OCTEON_DMA_BAR_TYPE_PCIE2) {
		msi_rcv_reg[0] = CVMX_PEXP_SLI_MSI_RCV0;
		msi_rcv_reg[1] = CVMX_PEXP_SLI_MSI_RCV1;
		msi_rcv_reg[2] = CVMX_PEXP_SLI_MSI_RCV2;
		msi_rcv_reg[3] = CVMX_PEXP_SLI_MSI_RCV3;
		msi_ena_reg[0] = CVMX_PEXP_SLI_MSI_ENB0;
		msi_ena_reg[1] = CVMX_PEXP_SLI_MSI_ENB1;
		msi_ena_reg[2] = CVMX_PEXP_SLI_MSI_ENB2;
		msi_ena_reg[3] = CVMX_PEXP_SLI_MSI_ENB3;
		msi = &octeon_irq_chip_msi_pcie;
		octeon_irq_msi_to_irq = octeon_irq_msi_to_irq_scatter;
		octeon_irq_irq_to_msi = octeon_irq_irq_to_msi_scatter;
		msi_map_reg = CVMX_PEXP_SLI_MSI_WR_MAP;
	} else if (octeon_dma_bar_type == OCTEON_DMA_BAR_TYPE_PCIE) {
		msi_rcv_reg[0] = CVMX_PEXP_NPEI_MSI_RCV0;
		msi_rcv_reg[1] = CVMX_PEXP_NPEI_MSI_RCV1;
		msi_rcv_reg[2] = CVMX_PEXP_NPEI_MSI_RCV2;
		msi_rcv_reg[3] = CVMX_PEXP_NPEI_MSI_RCV3;
		msi_ena_reg[0] = CVMX_PEXP_NPEI_MSI_ENB0;
		msi_ena_reg[1] = CVMX_PEXP_NPEI_MSI_ENB1;
		msi_ena_reg[2] = CVMX_PEXP_NPEI_MSI_ENB2;
		msi_ena_reg[3] = CVMX_PEXP_NPEI_MSI_ENB3;
		msi = &octeon_irq_chip_msi_pcie;
		octeon_irq_msi_to_irq = octeon_irq_msi_to_irq_scatter;
		octeon_irq_irq_to_msi = octeon_irq_irq_to_msi_scatter;
		msi_map_reg = CVMX_PEXP_NPEI_MSI_WR_MAP;
	} else {
		msi_rcv_reg[0] = CVMX_NPI_NPI_MSI_RCV;
#define INVALID_GENERATE_ADE 0x8700000000000000ULL;
		msi_rcv_reg[1] = INVALID_GENERATE_ADE;
		msi_rcv_reg[2] = INVALID_GENERATE_ADE;
		msi_rcv_reg[3] = INVALID_GENERATE_ADE;
		msi_ena_reg[0] = INVALID_GENERATE_ADE;
		msi_ena_reg[1] = INVALID_GENERATE_ADE;
		msi_ena_reg[2] = INVALID_GENERATE_ADE;
		msi_ena_reg[3] = INVALID_GENERATE_ADE;
		msi = &octeon_irq_chip_msi_pci;
		octeon_irq_msi_to_irq = octeon_irq_msi_to_irq_linear;
		octeon_irq_irq_to_msi = octeon_irq_irq_to_msi_linear;
		msi_map_reg = 0;
	}

	if (msi_map_reg) {
		int msi;
		int ciu;
		u64 e;

		for (msi = 0; msi < 256; msi++) {
			ciu = (msi >> 2) | ((msi << 6) & 0xc0);
			e = (ciu << 8) | msi;
			cvmx_write_csr(msi_map_reg, e);
		}
	}

	for (irq = OCTEON_IRQ_MSI_BIT0; irq <= OCTEON_IRQ_MSI_LAST; irq++)
		irq_set_chip_and_handler(irq, msi, handle_simple_irq);

	if (octeon_has_feature(OCTEON_FEATURE_PCIE)) {
		if (request_irq(OCTEON_IRQ_PCI_MSI0, octeon_msi_interrupt0,
				0, "MSI[0:63]", octeon_msi_interrupt0))
			panic("request_irq(OCTEON_IRQ_PCI_MSI0) failed");

		if (request_irq(OCTEON_IRQ_PCI_MSI1, octeon_msi_interrupt1,
				0, "MSI[64:127]", octeon_msi_interrupt1))
			panic("request_irq(OCTEON_IRQ_PCI_MSI1) failed");

		if (request_irq(OCTEON_IRQ_PCI_MSI2, octeon_msi_interrupt2,
				0, "MSI[127:191]", octeon_msi_interrupt2))
			panic("request_irq(OCTEON_IRQ_PCI_MSI2) failed");

		if (request_irq(OCTEON_IRQ_PCI_MSI3, octeon_msi_interrupt3,
				0, "MSI[192:255]", octeon_msi_interrupt3))
			panic("request_irq(OCTEON_IRQ_PCI_MSI3) failed");

		msi_irq_size = 256;
	} else if (octeon_is_pci_host()) {
		if (request_irq(OCTEON_IRQ_PCI_MSI0, octeon_msi_interrupt0,
				0, "MSI[0:15]", octeon_msi_interrupt0))
			panic("request_irq(OCTEON_IRQ_PCI_MSI0) failed");

		if (request_irq(OCTEON_IRQ_PCI_MSI1, octeon_msi_interrupt0,
				0, "MSI[16:31]", octeon_msi_interrupt0))
			panic("request_irq(OCTEON_IRQ_PCI_MSI1) failed");

		if (request_irq(OCTEON_IRQ_PCI_MSI2, octeon_msi_interrupt0,
				0, "MSI[32:47]", octeon_msi_interrupt0))
			panic("request_irq(OCTEON_IRQ_PCI_MSI2) failed");

		if (request_irq(OCTEON_IRQ_PCI_MSI3, octeon_msi_interrupt0,
				0, "MSI[48:63]", octeon_msi_interrupt0))
			panic("request_irq(OCTEON_IRQ_PCI_MSI3) failed");
		msi_irq_size = 64;
	}
	return 0;
}
subsys_initcall(octeon_msi_initialize);
