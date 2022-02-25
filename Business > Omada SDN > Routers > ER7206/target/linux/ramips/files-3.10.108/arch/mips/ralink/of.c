/*
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation.
 *
 * Copyright (C) 2008 Imre Kaloz <kaloz@openwrt.org>
 * Copyright (C) 2008-2009 Gabor Juhos <juhosg@openwrt.org>
 * Copyright (C) 2013 John Crispin <blogic@openwrt.org>
 */

#include <linux/io.h>
#include <linux/clk.h>
#include <linux/init.h>
#include <linux/sizes.h>
#include <linux/of_fdt.h>
#include <linux/kernel.h>
#include <linux/bootmem.h>
#include <linux/of_platform.h>
#include <linux/of_address.h>

#include <asm/reboot.h>
#include <asm/bootinfo.h>
#include <asm/addrspace.h>

#include "common.h"

__iomem void *rt_sysc_membase;
__iomem void *rt_memc_membase;

void __init device_tree_init(void)
{
	unsigned long base, size;
	void *fdt_copy;

	if (!initial_boot_params)
		return;

	base = virt_to_phys((void *)initial_boot_params);
	size = be32_to_cpu(initial_boot_params->totalsize);

	/* Before we do anything, lets reserve the dt blob */
	reserve_bootmem(base, size, BOOTMEM_DEFAULT);

	/* The strings in the flattened tree are referenced directly by the
	 * device tree, so copy the flattened device tree from init memory
	 * to regular memory.
	 */
	fdt_copy = alloc_bootmem(size);
	memcpy(fdt_copy, initial_boot_params, size);
	initial_boot_params = fdt_copy;

	unflatten_device_tree();

	/* free the space reserved for the dt blob */
	free_bootmem(base, size);
}

