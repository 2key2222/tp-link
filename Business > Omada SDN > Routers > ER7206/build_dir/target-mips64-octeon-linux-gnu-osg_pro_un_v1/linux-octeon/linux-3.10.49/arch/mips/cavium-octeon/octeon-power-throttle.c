/*
 * octeon-power-throttle.c - interface for controlling power
 * throttling on OCTEON II based platforms (6xxx and above).  OCTEON II
 * supports dynamic power control which aids to cut down power
 * consumption. The code exposes a "percentage" power throttling
 * limiter by means of /sys interface for each available cpu. Setting
 * this value to 0 will set power consumption to a minimum as it will
 * only execute a couple instructions every PERIOD as set in the
 * PowThrottle register.  If set to 100% for that particular cpu, it
 * may consume maximum power.
 *
 * Copyright (C) 2012 Cavium, Inc.
 *
 * Copyright (C) 2012 MontaVista LLC.
 * Author: Philby John <pjohn@mvista.com>
 * Credits: This driver is derived from Dmitriy Zavin's (dmitriyz@google.com)
 * thermal throttle event support code.
 */
#include <linux/kernel.h>
#include <linux/stat.h>
#include <linux/init.h>
#include <linux/smp.h>
#include <linux/cpu.h>
#include <linux/moduleparam.h>

#include <asm/byteorder.h>
#include <asm/octeon/octeon.h>

union octeon_power_throttle_bits {
	u64 raw;
	struct {
#ifdef __BIG_ENDIAN_BITFIELD
		u64 maxpow:8;		/* 63:56 */
		u64 powe:8;		/* 55:48 */
		u64 thrott:8;		/* 47:40 */
		u64 hrmpowadj:8;	/* 39:32 reserved in cn63XX */
		u64 reserved:3;		/* 31:29 */
		u64 ovrrd:1;		/* 28  reserved in cn63XX */
		u64 distag:1;		/* 27 */
		u64 period:3;		/* 26:24 */
		u64 powlim:8;		/* 23:16 */
		u64 maxthr:8;		/* 15:8 */
		u64 minthr:8;		/* 7:0 */
#else
		u64 minthr:8;
		u64 maxthr:8;
		u64 powlim:8;
		u64 period:3;
		u64 distag:1;
		u64 ovrrd:1;
		u64 reserved:3;
		u64 hrmpowadj:8;
		u64 thrott:8;
		u64 powe:8;
		u64 maxpow:8;
#endif
	} s;
};

/*
 * Boot-time power limit as percentage,
 * set with bootparam: octeon_power_throttle.start=85
 * Useful for situations where full-throttle boot would exceed power budget.
 * Individual cores' power can be throttled up/down after boot.
 */
static int boot_powlim = 100;
module_param_named(start, boot_powlim, int, 0444);

/* IPI calls to ask target CPU to access own registers ... */
static inline void read_my_power_throttle(void *info)
{
	*(u64*)info = __read_64bit_c0_register($11, 6);
}

static inline void write_my_power_throttle(void *info)
{
	__write_64bit_c0_register($11, 6, *(u64*)info);
}

/*
 * Read/Write POW_THROTTLE.
 */
static void octeon_power_throttle_csr_op(int cpu,
	union octeon_power_throttle_bits *r, bool write)
{
	smp_call_function_single(cpu, 
		(write ? write_my_power_throttle
		       : read_my_power_throttle),
		r, 1);
}

/*
 * Throttle given CPU's power (or all, if cpu < 0)
 */
static void octeon_power_throttle_init_cpu(int cpu)
{
	union octeon_power_throttle_bits r;
	octeon_power_throttle_csr_op(cpu, &r, false);

	r.s.ovrrd = 0;		/* MBZ */
	r.s.distag = 0;		/* MBZ */
	r.s.period = 2;		/* 256 cycles */
	r.s.minthr = 0;
	/* start at max allowed speed, subject to bootparams */
	r.s.maxthr = 0xff;
	r.s.powlim = 0xff * boot_powlim / 100;

	octeon_power_throttle_csr_op(cpu, &r, true);
}

/*
 * Get the POWLIM field as percentage% of the MAXPOW field in r.
 */
static int octeon_power_throttle_get_powlim(unsigned int cpu)
{
	int t, rv;
	union octeon_power_throttle_bits r;

	octeon_power_throttle_csr_op(cpu, &r, false);
	t = r.s.maxpow;
	if (!OCTEON_IS_MODEL(OCTEON_CN63XX)) {
		if (t < r.s.hrmpowadj)
			return -EINVAL;
		t -= r.s.hrmpowadj;
	}
	if (t > 0)
		rv = (r.s.powlim * 100) / t;
	else
		rv = 100;

	return rv > 100 ? 100 : rv;
}

/*
 * Set the POWLIM field as percentage% of the MAXPOW field in r.
 */
static u64 octeon_power_throttle_set_powlim(int cpu, unsigned long percentage)
{
	u64 t;
	u64 ret = 0;
	union octeon_power_throttle_bits r;

	if (percentage > 100)
		return -EINVAL;

	get_online_cpus();
	if (cpu_online(cpu)) {
		octeon_power_throttle_csr_op(cpu, &r, false);
		t = r.s.maxpow;
		if (!OCTEON_IS_MODEL(OCTEON_CN63XX)) {
			if (t < r.s.hrmpowadj)
				ret = -EINVAL;
			else
				t -= r.s.hrmpowadj;
		}
		r.s.powlim = percentage > 0 ? percentage * t / 100 : 0;
		r.s.ovrrd = 0;		/* MBZ */
		r.s.distag = 0;		/* MBZ */
		if (!ret)
			octeon_power_throttle_csr_op(cpu, &r, true);
	}
	put_online_cpus();

	return 0;
}

static ssize_t octeon_power_throttle_show_percentage(
	struct device *dev,
	struct device_attribute *attr,
	char *buf)
{
	unsigned int cpu = dev->id;
	ssize_t ret;

	get_online_cpus();
	if (cpu_online(cpu))
		ret = sprintf(buf, "%d\n",
			      octeon_power_throttle_get_powlim(cpu));
	else
		ret = 0;
	put_online_cpus();

	return ret;
}

static ssize_t octeon_power_throttle_store_percentage(
	struct device *dev,
	struct device_attribute *attr,
	const char *buf,
	size_t size)
{
	unsigned int cpu = dev->id;
	unsigned long val;
	int error;

	error = kstrtoul(buf, 0, &val);
	if (error)
		return error;

	get_online_cpus();
	if (cpu_online(cpu))
		octeon_power_throttle_set_powlim(cpu, val);
	put_online_cpus();

	return size;
}

static DEVICE_ATTR(percentage, S_IRUGO | S_IWUSR,
		   octeon_power_throttle_show_percentage,
		   octeon_power_throttle_store_percentage);

static struct attribute *octeon_power_throttle_attrs[] = {
	&dev_attr_percentage.attr,
	NULL
};

static struct attribute_group octeon_power_throttle_attr_group = {
	.attrs	= octeon_power_throttle_attrs,
	.name	= "power_throttle"
};

static __cpuinit int octeon_power_throttle_add_dev(struct device *dev)
{
	return sysfs_create_group(&dev->kobj,
				  &octeon_power_throttle_attr_group);
}

static __init int octeon_power_throttle_init(void)
{
	unsigned int cpu = 0;
	int err = 0;

	if (!(current_cpu_type() == CPU_CAVIUM_OCTEON2 ||
		current_cpu_type() == CPU_CAVIUM_OCTEON3))
		return 0;

	get_online_cpus();
	/* connect live CPUs to sysfs */
	for_each_present_cpu(cpu) {
		err = octeon_power_throttle_add_dev(get_cpu_device(cpu));
		if (err) {
			pr_err("Error: octeon_power_throttle_add_dev() failed\n");
			break;
		}
		octeon_power_throttle_init_cpu(cpu);
	}
	put_online_cpus();
	return err;
}
device_initcall(octeon_power_throttle_init);
