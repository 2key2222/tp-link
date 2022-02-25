/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2007, 2008, 2009, 2010, 2011 Cavium Networks
 */
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/pci.h>
#include <linux/interrupt.h>
#include <linux/time.h>
#include <linux/delay.h>
#include <linux/module.h>

#include <asm/octeon/octeon.h>
#include <asm/octeon/cvmx-npei-defs.h>
#include <asm/octeon/cvmx-pciercx-defs.h>
#include <asm/octeon/cvmx-pescx-defs.h>
#include <asm/octeon/cvmx-pexp-defs.h>
#include <asm/octeon/cvmx-pemx-defs.h>
#include <asm/octeon/cvmx-dpi-defs.h>
#include <asm/octeon/cvmx-rst-defs.h>
#include <asm/octeon/cvmx-sli-defs.h>
#include <asm/octeon/cvmx-sriox-defs.h>
#include <asm/octeon/cvmx-helper-errata.h>
#include <asm/octeon/pci-octeon.h>
#include <asm/octeon/cvmx-pcie.h>
/* Module parameter to disable PCI probing */
static int pcie_disable;
module_param(pcie_disable, int, S_IRUGO);

static int enable_pcie_14459_war;
static int enable_pcie_bus_num_war[CVMX_PCIE_MAX_PORTS];

/**
 * Map a PCI device to the appropriate interrupt line
 *
 * @dev:    The Linux PCI device structure for the device to map
 * @slot:   The slot number for this device on __BUS 0__. Linux
 *		 enumerates through all the bridges and figures out the
 *		 slot on Bus 0 where this device eventually hooks to.
 * @pin:    The PCI interrupt pin read from the device, then swizzled
 *		 as it goes through each bridge.
 * Returns Interrupt number for the device
 */
int __init octeon_pcie_pcibios_map_irq(const struct pci_dev *dev,
				       u8 slot, u8 pin)
{
	/*
	 * The EBH5600 board with the PCI to PCIe bridge mistakenly
	 * wires the first slot for both device id 2 and interrupt
	 * A. According to the PCI spec, device id 2 should be C. The
	 * following kludge attempts to fix this.
	 */
	if (strstr(octeon_board_type_string(), "EBH5600") &&
	    dev->bus && dev->bus->parent) {
		/*
		 * Iterate all the way up the device chain and find
		 * the root bus.
		 */
		while (dev->bus && dev->bus->parent)
			dev = to_pci_dev(dev->bus->bridge);
		/*
		 * If the root bus is number 0 and the PEX 8114 is the
		 * root, assume we are behind the miswired bus. We
		 * need to correct the swizzle level by two. Yuck.
		 */
		if ((dev->bus->number == 1) &&
		    (dev->vendor == 0x10b5) && (dev->device == 0x8114)) {
			/*
			 * The pin field is one based, not zero. We
			 * need to swizzle it by minus two.
			 */
			pin = ((pin - 3) & 3) + 1;
		}
	}
	/*
	 * The -1 is because pin starts with one, not zero. It might
	 * be that this equation needs to include the slot number, but
	 * I don't have hardware to check that against.
	 */
	return pin - 1 + OCTEON_IRQ_PCI_INT0;
}

static	void set_cfg_read_retry(u32 retry_cnt)
{
	union cvmx_pemx_ctl_status pemx_ctl;
	pemx_ctl.u64 = cvmx_read_csr(CVMX_PEMX_CTL_STATUS(1));
	pemx_ctl.cn63xx.cfg_rtry = retry_cnt;
	cvmx_write_csr(CVMX_PEMX_CTL_STATUS(1), pemx_ctl.u64);
}


static u32 disable_cfg_read_retry(void)
{
	u32 retry_cnt;

	union cvmx_pemx_ctl_status pemx_ctl;
	pemx_ctl.u64 = cvmx_read_csr(CVMX_PEMX_CTL_STATUS(1));
	retry_cnt =  pemx_ctl.cn63xx.cfg_rtry;
	pemx_ctl.cn63xx.cfg_rtry = 0;
	cvmx_write_csr(CVMX_PEMX_CTL_STATUS(1), pemx_ctl.u64);
	return retry_cnt;
}

static int is_cfg_retry(void)
{
	union cvmx_pemx_int_sum pemx_int_sum;
	pemx_int_sum.u64 = cvmx_read_csr(CVMX_PEMX_INT_SUM(1));
	if (pemx_int_sum.s.crs_dr)
		return 1;
	return 0;
}

/*
 * Read a value from configuration space
 *
 */
static int octeon_pcie_read_config(struct pci_bus *bus, unsigned int devfn,
				   int reg, int size, u32 *val)
{
	union octeon_cvmemctl cvmmemctl;
	union octeon_cvmemctl cvmmemctl_save;
	int bus_number = bus->number;
	int cfg_retry = 0;
	int retry_cnt = 0;
	int max_retry_cnt = 10;
	u32 cfg_retry_cnt = 0;
	unsigned int pcie_port = pci_domain_nr(bus);

	cvmmemctl_save.u64 = 0;
	BUG_ON(pcie_port >= ARRAY_SIZE(enable_pcie_bus_num_war));
	/*
	 * For the top level bus make sure our hardware bus number
	 * matches the software one
	 */
	if (bus->parent == NULL) {
		if (enable_pcie_bus_num_war[pcie_port])
			bus_number = 0;
		else {
			union cvmx_pciercx_cfg006 pciercx_cfg006;
			pciercx_cfg006.u32 = cvmx_pcie_cfgx_read(pcie_port,
					     CVMX_PCIERCX_CFG006(pcie_port));
			if (pciercx_cfg006.s.pbnum != bus_number) {
				pciercx_cfg006.s.pbnum = bus_number;
				pciercx_cfg006.s.sbnum = bus_number;
				pciercx_cfg006.s.subbnum = bus_number;
				cvmx_pcie_cfgx_write(pcie_port,
					    CVMX_PCIERCX_CFG006(pcie_port),
					    pciercx_cfg006.u32);
			}
		}
	}

	/*
	 * PCIe only has a single device connected to Octeon. It is
	 * always device ID 0. Don't bother doing reads for other
	 * device IDs on the first segment.
	 */
	if ((bus->parent == NULL) && (devfn >> 3 != 0))
		return PCIBIOS_FUNC_NOT_SUPPORTED;

	/*
	 * The following is a workaround for the CN57XX, CN56XX,
	 * CN55XX, and CN54XX errata with PCIe config reads from non
	 * existent devices.  These chips will hang the PCIe link if a
	 * config read is performed that causes a UR response.
	 */
	if (OCTEON_IS_MODEL(OCTEON_CN56XX_PASS1) ||
	    OCTEON_IS_MODEL(OCTEON_CN56XX_PASS1_1)) {
		/*
		 * For our EBH5600 board, port 0 has a bridge with two
		 * PCI-X slots. We need a new special checks to make
		 * sure we only probe valid stuff.  The PCIe->PCI-X
		 * bridge only respondes to device ID 0, function
		 * 0-1
		 */
		if ((bus->parent == NULL) && (devfn >= 2))
			return PCIBIOS_FUNC_NOT_SUPPORTED;
		/*
		 * The PCI-X slots are device ID 2,3. Choose one of
		 * the below "if" blocks based on what is plugged into
		 * the board.
		 */
#if 1
		/* Use this option if you aren't using either slot */
		if (bus_number == 2)
			return PCIBIOS_FUNC_NOT_SUPPORTED;
#elif 0
		/*
		 * Use this option if you are using the first slot but
		 * not the second.
		 */
		if ((bus_number == 2) && (devfn >> 3 != 2))
			return PCIBIOS_FUNC_NOT_SUPPORTED;
#elif 0
		/*
		 * Use this option if you are using the second slot
		 * but not the first.
		 */
		if ((bus_number == 2) && (devfn >> 3 != 3))
			return PCIBIOS_FUNC_NOT_SUPPORTED;
#elif 0
		/* Use this opion if you are using both slots */
		if ((bus_number == 2) &&
		    !((devfn == (2 << 3)) || (devfn == (3 << 3))))
			return PCIBIOS_FUNC_NOT_SUPPORTED;
#endif

		/* The following #if gives a more complicated example. This is
		   the required checks for running a Nitrox CN16XX-NHBX in the
		   slot of the EBH5600. This card has a PLX PCIe bridge with
		   four Nitrox PLX parts behind it */
#if 0
		/* PLX bridge with 4 ports */
		if ((bus_number == 4) &&
		    !((devfn >> 3 >= 1) && (devfn >> 3 <= 4)))
			return PCIBIOS_FUNC_NOT_SUPPORTED;
		/* Nitrox behind PLX 1 */
		if ((bus_number == 5) && (devfn >> 3 != 0))
			return PCIBIOS_FUNC_NOT_SUPPORTED;
		/* Nitrox behind PLX 2 */
		if ((bus_number == 6) && (devfn >> 3 != 0))
			return PCIBIOS_FUNC_NOT_SUPPORTED;
		/* Nitrox behind PLX 3 */
		if ((bus_number == 7) && (devfn >> 3 != 0))
			return PCIBIOS_FUNC_NOT_SUPPORTED;
		/* Nitrox behind PLX 4 */
		if ((bus_number == 8) && (devfn >> 3 != 0))
			return PCIBIOS_FUNC_NOT_SUPPORTED;
#endif

		/*
		 * Shorten the DID timeout so bus errors for PCIe
		 * config reads from non existent devices happen
		 * faster. This allows us to continue booting even if
		 * the above "if" checks are wrong.  Once one of these
		 * errors happens, the PCIe port is dead.
		 */
		cvmmemctl_save.u64 = __read_64bit_c0_register($11, 7);
		cvmmemctl.u64 = cvmmemctl_save.u64;
		cvmmemctl.s.didtto = 2;
		__write_64bit_c0_register($11, 7, cvmmemctl.u64);
	}

	if ((OCTEON_IS_MODEL(OCTEON_CN63XX)) && (enable_pcie_14459_war))
		cfg_retry_cnt = disable_cfg_read_retry();

	pr_debug("pcie_cfg_rd port=%d b=%d devfn=0x%03x reg=0x%03x"
		 " size=%d ", pcie_port, bus_number, devfn, reg, size);
	do {
		switch (size) {
		case 4:
			*val = cvmx_pcie_config_read32(pcie_port, bus_number,
				devfn >> 3, devfn & 0x7, reg);
		break;
		case 2:
			*val = cvmx_pcie_config_read16(pcie_port, bus_number,
				devfn >> 3, devfn & 0x7, reg);
		break;
		case 1:
			*val = cvmx_pcie_config_read8(pcie_port, bus_number,
				devfn >> 3, devfn & 0x7, reg);
		break;
		default:
			if (OCTEON_IS_MODEL(OCTEON_CN63XX))
				set_cfg_read_retry(cfg_retry_cnt);
			return PCIBIOS_FUNC_NOT_SUPPORTED;
		}
		if ((OCTEON_IS_MODEL(OCTEON_CN63XX)) &&
			(enable_pcie_14459_war)) {
			cfg_retry = is_cfg_retry();
			retry_cnt++;
			if (retry_cnt > max_retry_cnt) {
				pr_err(" pcie cfg_read retries failed. retry_cnt=%d\n",
				       retry_cnt);
				cfg_retry = 0;
			}
		}
	} while (cfg_retry);

	if ((OCTEON_IS_MODEL(OCTEON_CN63XX)) && (enable_pcie_14459_war))
		set_cfg_read_retry(cfg_retry_cnt);
	pr_debug("val=%08x  : tries=%02d\n", *val, retry_cnt);
	if (OCTEON_IS_MODEL(OCTEON_CN56XX_PASS1) ||
	    OCTEON_IS_MODEL(OCTEON_CN56XX_PASS1_1))
		write_c0_cvmmemctl(cvmmemctl_save.u64);
	return PCIBIOS_SUCCESSFUL;
}

static int octeon_dummy_read_config(struct pci_bus *bus, unsigned int devfn,
				    int reg, int size, u32 *val)
{
	return PCIBIOS_FUNC_NOT_SUPPORTED;
}

/*
 * Write a value to PCI configuration space
 */
static int octeon_pcie_write_config(struct pci_bus *bus, unsigned int devfn,
				    int reg, int size, u32 val)
{
	int bus_number = bus->number;
	unsigned int pcie_port = pci_domain_nr(bus);

	BUG_ON(pcie_port >= ARRAY_SIZE(enable_pcie_bus_num_war));

	if ((bus->parent == NULL) && (enable_pcie_bus_num_war[pcie_port]))
		bus_number = 0;

	pr_debug("pcie_cfg_wr port=%d b=%d devfn=0x%03x"
		 " reg=0x%03x size=%d val=%08x\n", pcie_port, bus_number, devfn,
		 reg, size, val);


	switch (size) {
	case 4:
		cvmx_pcie_config_write32(pcie_port, bus_number, devfn >> 3,
					 devfn & 0x7, reg, val);
		break;
	case 2:
		cvmx_pcie_config_write16(pcie_port, bus_number, devfn >> 3,
					 devfn & 0x7, reg, val);
		break;
	case 1:
		cvmx_pcie_config_write8(pcie_port, bus_number, devfn >> 3,
					devfn & 0x7, reg, val);
		break;
	default:
		return PCIBIOS_FUNC_NOT_SUPPORTED;
	}
#if PCI_CONFIG_SPACE_DELAY
	/*
	 * Delay on writes so that devices have time to come up. Some
	 * bridges need this to allow time for the secondary busses to
	 * work
	 */
	udelay(PCI_CONFIG_SPACE_DELAY);
#endif
	return PCIBIOS_SUCCESSFUL;
}

static int octeon_dummy_write_config(struct pci_bus *bus, unsigned int devfn,
				     int reg, int size, u32 val)
{
	return PCIBIOS_FUNC_NOT_SUPPORTED;
}

static struct pci_ops octeon_pcie_ops = {
	octeon_pcie_read_config,
	octeon_pcie_write_config,
};

#define OCTEON_PCIE_MEM_RESOURCE(PORT)				\
static struct resource octeon_pcie##PORT##_mem_resource = {	\
	.name = "Octeon PCIe##PORT## MEM",			\
	.flags = IORESOURCE_MEM,				\
};

#define OCTEON_PCIE_IO_RESOURCE(PORT)				\
static struct resource octeon_pcie##PORT##_io_resource = {	\
	.name = "Octeon PCIe##PORT## IO",			\
	.flags = IORESOURCE_IO,					\
};

#define OCTEON_PCIE_CONTROLLER(PORT)				\
static struct pci_controller octeon_pcie##PORT##_controller = {	\
	 .pci_ops = &octeon_pcie_ops,				\
	 .mem_resource = &octeon_pcie##PORT##_mem_resource,	\
	 .io_resource = &octeon_pcie##PORT##_io_resource,	\
};

OCTEON_PCIE_MEM_RESOURCE(0)
OCTEON_PCIE_MEM_RESOURCE(1)
OCTEON_PCIE_MEM_RESOURCE(2)
OCTEON_PCIE_IO_RESOURCE(0)
OCTEON_PCIE_IO_RESOURCE(1)
OCTEON_PCIE_IO_RESOURCE(2)
OCTEON_PCIE_CONTROLLER(0)
OCTEON_PCIE_CONTROLLER(1)
OCTEON_PCIE_CONTROLLER(2)

static struct pci_ops octeon_dummy_ops = {
	octeon_dummy_read_config,
	octeon_dummy_write_config,
};

static struct resource octeon_dummy_mem_resource = {
	.name = "Virtual PCIe MEM",
	.flags = IORESOURCE_MEM,
};

static struct resource octeon_dummy_io_resource = {
	.name = "Virtual PCIe IO",
	.flags = IORESOURCE_IO,
};

static struct pci_controller octeon_dummy_controller = {
	.pci_ops = &octeon_dummy_ops,
	.mem_resource = &octeon_dummy_mem_resource,
	.io_resource = &octeon_dummy_io_resource,
};

static int device_needs_bus_num_war(uint32_t deviceid)
{
#define IDT_VENDOR_ID 0x111d

	if ((deviceid  & 0xffff) == IDT_VENDOR_ID)
		return 1;
	return 0;
}

/**
 * Initialize the Octeon PCIe controllers
 *
 * Returns
 */
static int __init octeon_pcie_setup(void)
{
	int result;
	int host_mode = 0, port;
	int srio_war15205 = 0;
	union cvmx_sli_ctl_portx sli_ctl_portx;
	union cvmx_sriox_status_reg sriox_status_reg;

	/* These chips don't have PCIe */
	if (!octeon_has_feature(OCTEON_FEATURE_PCIE))
		return 0;

	/* No PCIe simulation */
	if (octeon_is_simulation())
		return 0;

	/* Disable PCI if instructed on the command line */
	if (pcie_disable)
		return 0;

	/* Point pcibios_map_irq() to the PCIe version of it */
	octeon_pcibios_map_irq = octeon_pcie_pcibios_map_irq;

	/*
	 * PCIe I/O range. It is based on port 0 but includes up until
	 * port 1's end.
	 */
	set_io_port_base(CVMX_ADD_IO_SEG(cvmx_pcie_get_io_base_address(0)));
	ioport_resource.start = 0;
	ioport_resource.end =
		cvmx_pcie_get_io_base_address(CVMX_PCIE_PORTS) -
		cvmx_pcie_get_io_base_address(0) + cvmx_pcie_get_io_size(1) - 1;

	/*
	 * Create a dummy PCIe controller to swallow up bus 0. IDT bridges
	 * don't work if the primary bus number is zero. Here we add a fake
	 * PCIe controller that the kernel will give bus 0. This allows
	 * us to not change the normal kernel bus enumeration
	 */
	octeon_dummy_controller.io_map_base = -1;
	octeon_dummy_controller.mem_resource->start = (1ull<<48);
	octeon_dummy_controller.mem_resource->end = (1ull<<48);
	register_pci_controller(&octeon_dummy_controller);

	for (port = 0; port < CVMX_PCIE_PORTS; port++) {
		if (octeon_has_feature(OCTEON_FEATURE_NPEI)) {
			if (port == 1) {
				host_mode = 1;
				/*
				 * Skip the 2nd port on CN52XX if port is in
				 * 4 lane mode
				 */
				if (OCTEON_IS_MODEL(OCTEON_CN52XX)) {
					union cvmx_npei_dbg_data dbg_data;
					dbg_data.u64 = cvmx_read_csr(CVMX_PEXP_NPEI_DBG_DATA);
					if (dbg_data.cn52xx.qlm0_link_width)
						host_mode = 0;
				}
			} else {
				union cvmx_npei_ctl_status npei_ctl_status;
				npei_ctl_status.u64 =
					cvmx_read_csr(CVMX_PEXP_NPEI_CTL_STATUS);
				host_mode = npei_ctl_status.s.host_mode;
				octeon_dma_bar_type = OCTEON_DMA_BAR_TYPE_PCIE;
			}
		} else {
			union cvmx_mio_rst_ctlx mio_rst_ctl;
			if (OCTEON_IS_OCTEON3())
				mio_rst_ctl.u64 = cvmx_read_csr(CVMX_RST_CTLX(port));
			else
				mio_rst_ctl.u64 = cvmx_read_csr(CVMX_MIO_RST_CTLX(port));
			host_mode = mio_rst_ctl.s.host_mode;
			if (port == 0)
				octeon_dma_bar_type = OCTEON_DMA_BAR_TYPE_PCIE2;
		}

		if (host_mode) {
			uint32_t device;
			pr_notice("PCIe: Initializing port %d\n", port);

			/* CN63XX pass 1_x/2.0 errata PCIe-15205 */
			if (OCTEON_IS_MODEL(OCTEON_CN63XX_PASS1_X) ||
				OCTEON_IS_MODEL(OCTEON_CN63XX_PASS2_0)) {
				sriox_status_reg.u64 = cvmx_read_csr(
						CVMX_SRIOX_STATUS_REG(port));
				if (sriox_status_reg.s.srio)
					/* Port is SRIO */
					srio_war15205 += 1;
			}
			result = cvmx_pcie_rc_initialize(port);
			if (result < 0)
				continue;

			/* Set IO offsets, Memory/IO resource start and end limits */
			switch (port) {
			case 0:
				/* Memory offsets are physical addresses */
				octeon_pcie0_controller.mem_offset =
					cvmx_pcie_get_mem_base_address(0);
				/*
				 * To calculate the address for accessing the 2nd PCIe device,
				 * either 'io_map_base' (pci_iomap()), or 'mips_io_port_base'
				 * (ioport_map()) value is added to
				 * pci_resource_start(dev,bar)). The 'mips_io_port_base' is set
				 * only once based on first PCIe. Also changing 'io_map_base'
				 * based on first slot's value so that both the routines will
				 * work properly.
				 */
				octeon_pcie0_controller.io_map_base =
					CVMX_ADD_IO_SEG(cvmx_pcie_get_io_base_address(0));
				/*
				 * To keep things similar to PCI, we start
				 * device addresses at the same place as PCI
				 * uisng big bar support. This normally
				 * translates to 4GB-256MB, which is the same
				 * as most x86 PCs.
				 */
				octeon_pcie0_controller.mem_resource->start =
					cvmx_pcie_get_mem_base_address(0) +
					(4ul << 30) - (OCTEON_PCI_BAR1_HOLE_SIZE << 20);
				octeon_pcie0_controller.mem_resource->end =
					cvmx_pcie_get_mem_base_address(0) +
					cvmx_pcie_get_mem_size(0) - 1;

				/* IO offsets are Mips virtual addresses */
				octeon_pcie0_controller.io_offset = 0;
				/*
				 * Ports must be above 16KB for the ISA bus
				 * filtering in the PCI-X to PCI bridge.
				 */
				octeon_pcie0_controller.io_resource->start = 4 << 10;
				octeon_pcie0_controller.io_resource->end =
					(cvmx_pcie_get_io_size(0) - 1);
				msleep(100); /* Some devices need extra time */
				octeon_pcie0_controller.index = 0;
				register_pci_controller(&octeon_pcie0_controller);
				break;
			case 1:
				octeon_pcie1_controller.mem_offset =
					cvmx_pcie_get_mem_base_address(1);
				octeon_pcie1_controller.io_map_base =
					CVMX_ADD_IO_SEG(cvmx_pcie_get_io_base_address(0));
				octeon_pcie1_controller.mem_resource->start =
					cvmx_pcie_get_mem_base_address(1) +
					(4ul << 30) - (OCTEON_PCI_BAR1_HOLE_SIZE << 20);
				octeon_pcie1_controller.mem_resource->end =
					cvmx_pcie_get_mem_base_address(1) +
					cvmx_pcie_get_mem_size(1) - 1;
				octeon_pcie1_controller.io_offset =
					cvmx_pcie_get_io_base_address(1) -
					cvmx_pcie_get_io_base_address(0);
				octeon_pcie1_controller.io_resource->start =
					(cvmx_pcie_get_io_base_address(1) -
					cvmx_pcie_get_io_base_address(0));
				octeon_pcie1_controller.io_resource->end =
					octeon_pcie1_controller.io_resource->start +
					cvmx_pcie_get_io_size(1) - 1;
				msleep(100); /* Some devices need extra time */
				octeon_pcie1_controller.index = 1;
				register_pci_controller(&octeon_pcie1_controller);
				break;
			case 2:
				octeon_pcie2_controller.mem_offset =
					cvmx_pcie_get_mem_base_address(2);
				octeon_pcie2_controller.io_map_base =
					CVMX_ADD_IO_SEG(cvmx_pcie_get_io_base_address(0));
				octeon_pcie2_controller.mem_resource->start =
					cvmx_pcie_get_mem_base_address(2) +
					(4ul << 30) - (OCTEON_PCI_BAR1_HOLE_SIZE << 20);
				octeon_pcie2_controller.mem_resource->end =
					cvmx_pcie_get_mem_base_address(2) +
					cvmx_pcie_get_mem_size(2) - 1;
				octeon_pcie2_controller.io_offset =
					cvmx_pcie_get_io_base_address(2) -
					cvmx_pcie_get_io_base_address(1);
				octeon_pcie2_controller.io_resource->start =
					cvmx_pcie_get_io_base_address(2) -
					cvmx_pcie_get_io_base_address(1);
				octeon_pcie2_controller.io_resource->end =
					octeon_pcie2_controller.io_resource->start +
					cvmx_pcie_get_io_size(2) - 1;
				msleep(100); /* Some devices need extra time */
				octeon_pcie2_controller.index = 2;
				register_pci_controller(&octeon_pcie2_controller);
				break;
			default:
				break;
			}
			device = cvmx_pcie_config_read32(port, 0, 0, 0, 0);
			enable_pcie_bus_num_war[port] =
				device_needs_bus_num_war(device);
		} else {
			pr_notice("PCIe: Port 0 in endpoint mode, skipping.\n");
			/* CN63XX pass 1_x/2.0 errata PCIe-15205 */
			if (OCTEON_IS_MODEL(OCTEON_CN63XX_PASS1_X) ||
				OCTEON_IS_MODEL(OCTEON_CN63XX_PASS2_0)) {
				srio_war15205 += 1;
			}
		}
	}

	/*
	 * CN63XX pass 1_x/2.0 errata PCIe-15205 requires setting all
	 * of SRIO MACs SLI_CTL_PORT*[INT*_MAP] to similar value and
	 * all of PCIe Macs SLI_CTL_PORT*[INT*_MAP] to different value
	 * from the previous set values
	 */
	for (port = 0; port < CVMX_PCIE_PORTS; port++) {
		if (OCTEON_IS_MODEL(OCTEON_CN63XX_PASS1_X) ||
		    OCTEON_IS_MODEL(OCTEON_CN63XX_PASS2_0)) {
			if (srio_war15205 == 1) {
				sli_ctl_portx.u64 = cvmx_read_csr(CVMX_PEXP_SLI_CTL_PORTX(port));
				sli_ctl_portx.s.inta_map = 1;
				sli_ctl_portx.s.intb_map = 1;
				sli_ctl_portx.s.intc_map = 1;
				sli_ctl_portx.s.intd_map = 1;
				cvmx_write_csr(CVMX_PEXP_SLI_CTL_PORTX(port), sli_ctl_portx.u64);

				sli_ctl_portx.u64 = cvmx_read_csr(CVMX_PEXP_SLI_CTL_PORTX(!port));
				sli_ctl_portx.s.inta_map = 0;
				sli_ctl_portx.s.intb_map = 0;
				sli_ctl_portx.s.intc_map = 0;
				sli_ctl_portx.s.intd_map = 0;
				cvmx_write_csr(CVMX_PEXP_SLI_CTL_PORTX(!port), sli_ctl_portx.u64);
			}
		}
	}

	octeon_pci_dma_init();

	return 0;
}
arch_initcall(octeon_pcie_setup);
