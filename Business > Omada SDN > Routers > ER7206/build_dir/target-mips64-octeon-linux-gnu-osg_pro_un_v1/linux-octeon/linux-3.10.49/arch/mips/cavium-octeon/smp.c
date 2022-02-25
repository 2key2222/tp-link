/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2004 - 2013 Cavium, Inc.
 */
#include <linux/cpu.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/smp.h>
#include <linux/interrupt.h>
#include <linux/kernel_stat.h>
#include <linux/sched.h>
#include <linux/module.h>

#include <asm/mmu_context.h>
#include <asm/time.h>
#include <asm/setup.h>

#include <asm/octeon/octeon.h>
#include <asm/octeon/octeon-boot-info.h>
#include <asm/octeon/cvmx-app-hotplug.h>
#include <asm/octeon/cvmx-spinlock.h>

unsigned long octeon_processor_boot = 0xff;
__cpuinitdata unsigned long octeon_processor_sp;
__cpuinitdata unsigned long octeon_processor_gp;

#ifdef CONFIG_HOTPLUG_CPU
static uint32_t octeon_hotplug_entry_addr;
extern asmlinkage void octeon_hotplug_entry(void);
static struct cvmx_app_hotplug_global *octeon_hotplug_global_ptr;
#endif

uint64_t octeon_bootloader_entry_addr;
EXPORT_SYMBOL(octeon_bootloader_entry_addr);

static unsigned long long boot_core_mask;

static void octeon_icache_flush(void)
{
	asm volatile ("synci 0($0)\n");
}

#ifdef CONFIG_KEXEC
static void octeon_crash_dump(void)
{
	if (dump_ipi_function_ptr)
		dump_ipi_function_ptr(NULL);
}
#endif

static octeon_message_fn_t  octeon_message_functions[8] = {
	scheduler_ipi,
	smp_call_function_interrupt,
	octeon_icache_flush,
#ifdef CONFIG_KEXEC
	octeon_crash_dump,
#endif
};

static  int octeon_message_free_mask = 0xf8;
static DEFINE_SPINLOCK(octeon_message_functions_lock);

int octeon_request_ipi_handler(octeon_message_fn_t fn)
{
	int i;
	int message;
	spin_lock(&octeon_message_functions_lock);

	for (i = 0; i < ARRAY_SIZE(octeon_message_functions); i++) {
		message = (1 << i);
		if (message & octeon_message_free_mask) {
			/* found a slot. */
			octeon_message_free_mask ^= message;
			octeon_message_functions[i] = fn;
			goto out;
		}
	}
	message = -ENOMEM;
out:
	spin_unlock(&octeon_message_functions_lock);
	return message;
}
EXPORT_SYMBOL(octeon_request_ipi_handler);

void octeon_release_ipi_handler(int action)
{
	int i;
	int message;
	spin_lock(&octeon_message_functions_lock);

	for (i = 0; i < ARRAY_SIZE(octeon_message_functions); i++) {
		message = (1 << i);
		if (message == action) {
			octeon_message_functions[i] = NULL;
			octeon_message_free_mask |= message;
			goto out;
		}
	}
	pr_err("octeon_release_ipi_handler: Unknown action: %x\n", action);
out:
	spin_unlock(&octeon_message_functions_lock);
}
EXPORT_SYMBOL(octeon_release_ipi_handler);

static irqreturn_t mailbox_interrupt(int irq, void *dev_id)
{
	u64 mbox_clrx = CVMX_CIU_MBOX_CLRX(cvmx_get_core_num());
	u64 action;
	int i;

	/*
	 * Make sure the function array initialization remains
	 * correct.
	 */
	BUILD_BUG_ON(SMP_RESCHEDULE_YOURSELF != (1 << 0));
	BUILD_BUG_ON(SMP_CALL_FUNCTION       != (1 << 1));
	BUILD_BUG_ON(SMP_ICACHE_FLUSH        != (1 << 2));

	/*
	 * Load the mailbox register to figure out what we're supposed
	 * to do.
	 */
	action = cvmx_read_csr(mbox_clrx);

	if (OCTEON_IS_MODEL(OCTEON_CN68XX))
		action &= 0xff;
	else
		action &= 0xffff;

	/* Clear the mailbox to clear the interrupt */
	cvmx_write_csr(mbox_clrx, action);

	for (i = 0; i < ARRAY_SIZE(octeon_message_functions) && action;) {
		if (action & 1) {
			octeon_message_fn_t fn = octeon_message_functions[i];
			if (fn)
				fn();
		}
		action >>= 1;
		i++;
	}
	return IRQ_HANDLED;
}

/**
 * Cause the function described by call_data to be executed on the passed
 * cpu.	 When the function has finished, increment the finished field of
 * call_data.
 */
void octeon_send_ipi_single(int cpu, unsigned int action)
{
	int coreid = cpu_logical_map(cpu);
	cvmx_write_csr(CVMX_CIU_MBOX_SETX(coreid), action);
}
EXPORT_SYMBOL(octeon_send_ipi_single);

static inline void octeon_send_ipi_mask(const struct cpumask *mask,
					unsigned int action)
{
	int cpu;

	for_each_cpu(cpu, mask)
		octeon_send_ipi_single(cpu, action);
}

#ifdef CONFIG_HOTPLUG_CPU

/*
 * Initialize the content of struct * cvmx_app_hotplug_global
 * if it is allocated, atomically.
 */
static void octeon_hotplug_global_init(void *arg)
{
	struct linux_app_boot_info *labi;
	cvmx_app_hotplug_global_t *hgp = arg;
	memset(hgp, 0, CVMX_APP_HOTPLUG_INFO_REGION_SIZE);

	hgp->magic_version = CVMX_HOTPLUG_MAGIC_VERSION;

	cvmx_spinlock_init(&hgp->hotplug_global_lock);

	/* Get legacy LABI data structure for initial parameters */
	labi = phys_to_virt(LABI_ADDR_IN_BOOTLOADER);

	/* Valicate signature */
	if (labi->labi_signature != LABI_SIGNATURE)
		return;

	/* Initialize available cores from LABI */
	cvmx_coremask_set64(&hgp->avail_coremask,
		(uint64_t) labi->avail_coremask);
}
#endif

static void octeon_smp_setup(void)
{
	const int coreid = cvmx_get_core_num();
	int cpus;
	int id;
	struct linux_app_boot_info *labi;
#ifdef CONFIG_HOTPLUG_CPU
	unsigned int num_cores = cvmx_octeon_num_cores();
	struct cvmx_app_hotplug_global *hgp;
	char hexstr[CVMX_MIPS_MAX_CORES/4+1];
	unsigned long t;
#endif

	boot_core_mask = octeon_get_boot_coremask();

	labi = phys_to_virt(LABI_ADDR_IN_BOOTLOADER);

	if (labi->labi_signature == LABI_SIGNATURE) {
		octeon_bootloader_entry_addr = labi->InitTLBStart_addr;
	}

	/* The present CPUs are initially just the boot cpu (CPU 0). */
	for (id = 0; id < NR_CPUS; id++) {
		set_cpu_possible(id, id == 0);
		set_cpu_present(id, id == 0);
	}

	__cpu_number_map[coreid] = 0;
	__cpu_logical_map[0] = coreid;

	/* The present CPUs get the lowest CPU numbers. */
	cpus = 1;
	for (id = 0; id < NR_CPUS; id++) {
		if ((id != coreid) && (boot_core_mask & (1 << id))) {
			set_cpu_possible(cpus, true);
			set_cpu_present(cpus, true);
			__cpu_number_map[id] = cpus;
			__cpu_logical_map[cpus] = id;
			cpus++;
		}
	}

#ifdef CONFIG_HOTPLUG_CPU
	t = __pa_symbol(octeon_hotplug_entry);

	if (t < 0x20000000)
		octeon_hotplug_entry_addr = (uint32_t)CKSEG0ADDR(t);

	/*
	 * The possible CPUs are all those present on the chip.	 We
	 * will assign CPU numbers for possible cores as well.	Cores
	 * are always consecutively numberd from 0.
	 */
	for (id = 0; id < num_cores && id < NR_CPUS; id++) {
		if (!(boot_core_mask & (1 << id))) {
			set_cpu_possible(cpus, true);
			__cpu_number_map[id] = cpus;
			__cpu_logical_map[cpus] = id;
			cpus++;
		}
	}

	/* Atomically allocate Hotplug global structure */
	hgp = (struct cvmx_app_hotplug_global *)
		cvmx_bootmem_alloc_named_range_once(
			CVMX_APP_HOTPLUG_INFO_REGION_SIZE,
			0x0, 0x0, 0,
			CVMX_APP_HOTPLUG_INFO_REGION_NAME,
			octeon_hotplug_global_init
		);
	if (!hgp) {
		pr_err("Failed to allocate memory for Hotplug memory block\n");
		octeon_hotplug_entry_addr = 0;
		return;
	}

	/* Validate magic number */
	if (hgp->magic_version != CVMX_HOTPLUG_MAGIC_VERSION) {
		pr_err("Cavium Hotplug: data record invalid\n");
		octeon_hotplug_entry_addr = 0;
		return;
	}

	/* Convert coremask to string for printing */
	cvmx_coremask_bmp2str(&hgp->avail_coremask, hexstr);

	/* Print the available coremask on to the console */
	pr_info("Cavium Hotplug: Available coremask 0x%s\n", hexstr);

	/* Set global ptr for use by other functions */
	octeon_hotplug_global_ptr = hgp;
#endif
}

/**
 * Firmware CPU startup hook
 *
 */
static void __cpuinit octeon_boot_secondary(int cpu, struct task_struct *idle)
{
	int count;

	pr_info("SMP: Booting CPU%02d (CoreId %2d)...\n", cpu,
		cpu_logical_map(cpu));

	octeon_processor_sp = __KSTK_TOS(idle);
	octeon_processor_gp = (unsigned long)(task_thread_info(idle));
	/* This barrier is needed to guarangee the following is done last */
	mb();

	/* Indicate which core is being brought up out of pan */
	octeon_processor_boot = cpu_logical_map(cpu);

	/* Push the last update out before polling */
	mb();

	count = 10000;
	while (octeon_processor_sp && count) {
		/* Waiting for processor to get the SP and GP */
		udelay(1);
		count--;
		mb();
	}
	if (count == 0)
		pr_err("Secondary boot timeout\n");
}

/**
 * After we've done initial boot, this function is called to allow the
 * board code to clean up state, if needed
 */
static void __cpuinit octeon_init_secondary(void)
{
	unsigned int sr;

	sr = set_c0_status(ST0_BEV);
	write_c0_ebase((u32)ebase);
	write_c0_status(sr);

	octeon_check_cpu_bist();
	octeon_init_cvmcount();

	octeon_irq_setup_secondary();
}

/**
 * Callout to firmware before smp_init
 *
 */
void octeon_prepare_cpus(unsigned int max_cpus)
{
	u64 mask;
	u64 coreid;

	/*
	 * Only the low order mailbox bits are used for IPIs, leave
	 * the other bits alone.
	 */
	if (OCTEON_IS_MODEL(OCTEON_CN68XX))
		mask = 0xff;
	else
		mask = 0xffff;

	coreid = cvmx_get_core_num();

	/* Clear pending mailbox interrupts */
	cvmx_write_csr(CVMX_CIU_MBOX_CLRX(coreid), mask);

	/* Attach mailbox interrupt handler */
	if (request_irq(OCTEON_IRQ_MBOX0, mailbox_interrupt,
			IRQF_PERCPU | IRQF_NO_THREAD, "SMP-IPI",
			mailbox_interrupt)) {
		panic("Cannot request_irq(OCTEON_IRQ_MBOX0)");
	}
}

/**
 * Last chance for the board code to finish SMP initialization before
 * the CPU is "online".
 */
static void octeon_smp_finish(void)
{
	octeon_user_io_init();

	/* to generate the first CPU timer interrupt */
	write_c0_compare(read_c0_count() + mips_hpt_frequency / HZ);
	local_irq_enable();
}

/**
 * Hook for after all CPUs are online
 */
static void octeon_cpus_done(void)
{
#ifdef CONFIG_HOTPLUG_CPU
	struct cvmx_app_hotplug_global *hgp;
	char hexstr[CVMX_MIPS_MAX_CORES/4+1];
	unsigned int cpu;

	hgp = octeon_hotplug_global_ptr;

	/* Boot core_mask not needed any longer */
	boot_core_mask = 0;

	/* Boot core_mask CPUs are now all on-line,
	 * make the rest of the CPUs available for HOTPLUG
	 * regardless if they are presently available
	 */
	for_each_possible_cpu(cpu) {
		if (!cpu_online(cpu))
			set_cpu_present(cpu, true);
	}

	/* Convert coremask to string for printing */
	cvmx_coremask_bmp2str(&hgp->avail_coremask, hexstr);

	/* Print the available coremask on to the console */
	pr_info("Cavium Hotplug: Available coremask 0x%s\n", hexstr);
#endif
}

#ifdef CONFIG_HOTPLUG_CPU

/* State of each CPU. */
DEFINE_PER_CPU(int, cpu_state);

extern void fixup_irqs(void);

/*
 * Convert coremask to a printable hex string
 * Same function by name and purpose is also found in cvmx-coremask.c
 * but with a different implementation.
 */
int cvmx_coremask_bmp2str(const cvmx_coremask_t *pcm, char *hexstr)
{
	int core;
	char *p;
	unsigned int i;
	unsigned int nibbles;
	unsigned int num_cores = cvmx_octeon_num_cores();
	static const char hextab[16] = {
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		'a', 'b', 'c', 'd', 'e', 'f'};

	if (num_cores >= CVMX_MIPS_MAX_CORES)
		return -1;

	p = hexstr;

	/* round-up num_cores to modulus 4 */
	num_cores += 3;
	num_cores &= ~3;

	/* Calculate nibble count */
	nibbles = num_cores >> 2;

	/* Clear the buffer */
	for (i = 0; i <= nibbles; i++)
		p[i] = '\0';

	/* Place core bits into nibbles, 4 bits per nibble */
	for (core = num_cores - 1; core >= 0; core--) {
		if (cvmx_coremask_is_core_set(pcm, core))
			p[nibbles - (core>>2) - 1] |= 1 << (core & 3);
	}

	/* Convert each nibble into a hex char */
	for (i = 0; i < nibbles; i++)
		p[i] = hextab[p[i] & 0xf];

	p[i] = '\0';

	/* return the number if buffer bytes touched */
	return nibbles+1;
}

static int octeon_cpu_disable(void)
{
	unsigned int cpu = smp_processor_id();

	if (cpu == 0)
		return -EBUSY;

	set_cpu_online(cpu, false);
	cpu_clear(cpu, cpu_callin_map);
	fixup_irqs();
	flush_cache_all();
	local_flush_tlb_all();

	return 0;
}

static void octeon_cpu_die(unsigned int cpu)
{
	int coreid = cpu_logical_map(cpu);
	int node;
	struct cvmx_app_hotplug_global *hgp = octeon_hotplug_global_ptr;
	char hexstr[CVMX_MIPS_MAX_CORES/4+3];

	BUG_ON(!hgp);

	while (per_cpu(cpu_state, cpu) != CPU_DEAD)
		cpu_relax();

	cvmx_spinlock_lock(&hgp->hotplug_global_lock);
	cvmx_coremask_set_core(&hgp->avail_coremask, coreid);
	cvmx_spinlock_unlock(&hgp->hotplug_global_lock);

	mb();

	/* Convert coremask to string for printing */
	cvmx_coremask_bmp2str(&hgp->avail_coremask, hexstr);
	pr_info("Reset core %d. Available Coremask = 0x%s\n", coreid, hexstr);

	/* Covert coreid to node/core spec and send NMI to target core */
	node = cvmx_coremask_core_to_node(coreid);
	coreid = cvmx_coremask_core_on_node(coreid);
	cvmx_write_csr_node(node, CVMX_CIU_NMI, (1 << coreid));
}

void play_dead(void)
{
	int cpu = cpu_number_map(cvmx_get_core_num());
	register unsigned long v;
	v = ~0ULL;

	idle_task_exit();
	octeon_processor_boot = v;
	per_cpu(cpu_state, cpu) = CPU_DEAD;

	wmb(); /* nudge writeback */

#ifdef	CONFIG_CPU_LITTLE_ENDIAN
	/* Switch CPU core back to Big Endian mode */
	CVMX_MF_CVM_CTL(v);
	v &= ~2;
	CVMX_MT_CVM_CTL(v);
	mb();
#endif	/*CONFIG_CPU_LITTLE_ENDIAN*/

	while (1) {	/* core will be reset here */
		asm volatile ("nop\n wait\n nop\n");
	}
}

#ifdef	CONFIG_CPU_LITTLE_ENDIAN
# ifdef __BIG_ENDIAN_BITFIELD
#   error "Endian Configuration Mismatch"
# endif
#endif

static int octeon_update_boot_vector(unsigned int cpu)
{
	int coreid = cpu_logical_map(cpu);
	int node;
	struct cvmx_app_hotplug_global *hgp = octeon_hotplug_global_ptr;
	struct boot_init_vector *boot_vect =
		phys_to_virt(BOOTLOADER_BOOT_VECTOR);

	/* Verify that required entry points are known at this stage */
	if (!hgp || !octeon_hotplug_entry_addr ||
			!octeon_bootloader_entry_addr) {
		pr_warn("Cavium Hotplog: boot-loader incompatible with Hotplog\n");
		return -EINVAL;
	}

	/* Verify that coreid does not exceed the number of vector slots */
	if (coreid >= CVMX_MAX_CORES) {
		pr_warn("Cavium Hotplog: physical core %d is out of range\n",
			coreid );
		return -EINVAL;
	}

	/*
	 * A core being brought up must be present either in the boot
	 * core_mask or in the hotplug available coremask
	 */
	if (boot_core_mask & (1 << coreid)) {
		boot_core_mask &= ~(1 << coreid);
		/* CPU in boot core mask needs no further handling */
		return 0;
	}

	cvmx_spinlock_lock(&hgp->hotplug_global_lock);
	if (!cvmx_coremask_is_core_set(&hgp->avail_coremask, coreid)) {
		cvmx_spinlock_unlock(&hgp->hotplug_global_lock);
		pr_warn("Cavium Hotplog: cpu %u core %u is not available\n",
			cpu, coreid);
		return -EBUSY;
	}

	/* This core is no longer available */
	cvmx_coremask_clear_core(&hgp->avail_coremask, coreid);
	cvmx_spinlock_unlock(&hgp->hotplug_global_lock);

	/* boot_vect array has CVMX_MAX_CORES slots */
	boot_vect[coreid].app_start_func_addr = octeon_hotplug_entry_addr;
	boot_vect[coreid].code_addr = octeon_bootloader_entry_addr;

	mb();

	/* Convert coreid to node,core spair and send NMI to target core */
	node = cvmx_coremask_core_to_node(coreid);
	coreid = cvmx_coremask_core_on_node(coreid);
	cvmx_write_csr_node(node, CVMX_CIU_NMI, (1 << coreid));

	return 0;
}

static int __cpuinit octeon_cpu_callback(struct notifier_block *nfb,
	unsigned long action, void *hcpu)
{
	unsigned int cpu = (unsigned long)hcpu;
	int ret = 0;

	switch (action) {
	case CPU_UP_PREPARE_FROZEN:
	case CPU_UP_PREPARE:
		ret = octeon_update_boot_vector(cpu);
		if (ret)
			return notifier_from_errno(ret);
		break;
	case CPU_ONLINE_FROZEN:
	case CPU_ONLINE:
		pr_info("Cpu %d online\n", cpu);
		break;
	case CPU_DEAD_FROZEN:
	case CPU_DEAD:
		pr_info("Cpu %d offline\n", cpu);
		break;
	default:
		/* No action required for other events */
		break;
	}

	return NOTIFY_OK;
}

static struct notifier_block __cpuinitdata octeon_cpu_notifer = {
	.notifier_call = octeon_cpu_callback,
};

static int __cpuinit register_cavium_notifier(void)
{
	return register_cpu_notifier(&octeon_cpu_notifer);
}

early_initcall(register_cavium_notifier);

#endif	/* CONFIG_HOTPLUG_CPU */

static struct plat_smp_ops octeon_smp_ops = {
	.send_ipi_single	= octeon_send_ipi_single,
	.send_ipi_mask		= octeon_send_ipi_mask,
	.init_secondary		= octeon_init_secondary,
	.smp_finish		= octeon_smp_finish,
	.cpus_done		= octeon_cpus_done,
	.boot_secondary		= octeon_boot_secondary,
	.smp_setup		= octeon_smp_setup,
	.prepare_cpus		= octeon_prepare_cpus,
#ifdef CONFIG_HOTPLUG_CPU
	.cpu_disable		= octeon_cpu_disable,
	.cpu_die		= octeon_cpu_die,
#endif
};

static irqreturn_t octeon_78xx_reched_interrupt(int irq, void *dev_id)
{
	scheduler_ipi();
	return IRQ_HANDLED;
}

static irqreturn_t octeon_78xx_call_function_interrupt(int irq, void *dev_id)
{
	smp_call_function_interrupt();
	return IRQ_HANDLED;
}

static irqreturn_t octeon_78xx_icache_flush_interrupt(int irq, void *dev_id)
{
	octeon_icache_flush();
	return IRQ_HANDLED;
}

/*
 * Callout to firmware before smp_init
 */
static void octeon_78xx_prepare_cpus(unsigned int max_cpus)
{
	if (request_irq(OCTEON_IRQ_MBOX0 + 0, octeon_78xx_reched_interrupt,
			IRQF_PERCPU | IRQF_NO_THREAD, "Scheduler",
			octeon_78xx_reched_interrupt)) {
		panic("Cannot request_irq for SchedulerIPI");
	}
	if (request_irq(OCTEON_IRQ_MBOX0 + 1, octeon_78xx_call_function_interrupt,
			IRQF_PERCPU | IRQF_NO_THREAD, "SMP-Call",
			octeon_78xx_call_function_interrupt)) {
		panic("Cannot request_irq for SMP-Call");
	}
	if (request_irq(OCTEON_IRQ_MBOX0 + 2, octeon_78xx_icache_flush_interrupt,
			IRQF_PERCPU | IRQF_NO_THREAD, "ICache-Flush",
			octeon_78xx_icache_flush_interrupt)) {
		panic("Cannot request_irq for ICache-Flush");
	}
}

static void octeon_78xx_send_ipi_single(int cpu, unsigned int action)
{
	int i;

	for (i = 0; i < 8; i++) {
		if (action & 1)
			octeon_ciu3_mbox_send(cpu, i);
		action >>= 1;
	}
}

static void octeon_78xx_send_ipi_mask(const struct cpumask *mask,
				      unsigned int action)
{
	unsigned int cpu;

	for_each_cpu(cpu, mask)
		octeon_78xx_send_ipi_single(cpu, action);
}

static struct plat_smp_ops octeon_78xx_smp_ops = {
	.send_ipi_single	= octeon_78xx_send_ipi_single,
	.send_ipi_mask		= octeon_78xx_send_ipi_mask,
	.init_secondary		= octeon_init_secondary,
	.smp_finish		= octeon_smp_finish,
	.cpus_done		= octeon_cpus_done,
	.boot_secondary		= octeon_boot_secondary,
	.smp_setup		= octeon_smp_setup,
	.prepare_cpus		= octeon_78xx_prepare_cpus,
#ifdef CONFIG_HOTPLUG_CPU
	.cpu_disable		= octeon_cpu_disable,
	.cpu_die		= octeon_cpu_die,
#endif
};

void __init octeon_setup_smp(void)
{
	struct plat_smp_ops *ops;

	if (OCTEON_IS_MODEL(OCTEON_CN78XX))
		ops = &octeon_78xx_smp_ops;
	else
		ops = &octeon_smp_ops;

	register_smp_ops(ops);
}
