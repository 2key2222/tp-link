/*
 * System controller support for Armada 370, 375 and XP platforms.
 *
 * Copyright (C) 2012 Marvell
 *
 * Lior Amsalem <alior@marvell.com>
 * Gregory CLEMENT <gregory.clement@free-electrons.com>
 * Thomas Petazzoni <thomas.petazzoni@free-electrons.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 *
 * The Armada 370, 375 and Armada XP SoCs have a range of
 * miscellaneous registers, that do not belong to a particular device,
 * but rather provide system-level features. This basic
 * system-controller driver provides a device tree binding for those
 * registers, and implements utility functions offering various
 * features related to those registers.
 *
 * For now, the feature set is limited to restarting the platform by a
 * soft-reset, but it might be extended in the future.
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/of_address.h>
#include <linux/io.h>
#include <linux/reboot.h>
#include "common.h"
#include "mvebu-soc-id.h"
#include "pmsu.h"

#define ARMADA_375_CRYPT0_ENG_TARGET 41
#define ARMADA_375_CRYPT0_ENG_ATTR    1
#define SYSTEM_CONTROLLER_OFFSET 0x18200
#define GPIO_MPP_DATA_OUT_OFFSET 0x18100
#define GPIO_MPP_DATA_OUT_EN_OFFSET 0x18104

#define GPIO_MPP32_DATA_OUT_OFFSET 0x18140
#define GPIO_MPP32_DATA_OUT_EN_OFFSET 0x18144



static void __iomem *system_controller_base;
static phys_addr_t system_controller_phys_base;

struct mvebu_system_controller {
	u32 rstoutn_mask_offset;
	u32 system_soft_reset_offset;

	u32 rstoutn_mask_reset_out_en;
	u32 system_soft_reset;

	u32 resume_boot_addr;

	u32 dev_id;
	u32 rev_id;
};
static struct mvebu_system_controller *mvebu_sc;

static const struct mvebu_system_controller armada_370_xp_system_controller = {
	.rstoutn_mask_offset = 0x60,
	.system_soft_reset_offset = 0x64,
	.rstoutn_mask_reset_out_en = 0x1,
	.system_soft_reset = 0x1,
	.dev_id = 0x38,
	.rev_id = 0x3c,
};

static const struct mvebu_system_controller armada_375_system_controller = {
	.rstoutn_mask_offset = 0x54,
	.system_soft_reset_offset = 0x58,
	.rstoutn_mask_reset_out_en = 0x1,
	.system_soft_reset = 0x1,
	.resume_boot_addr = 0xd4,
	.dev_id = 0x38,
	.rev_id = 0x3c,
};

static const struct mvebu_system_controller orion_system_controller = {
	.rstoutn_mask_offset = 0x108,
	.system_soft_reset_offset = 0x10c,
	.rstoutn_mask_reset_out_en = 0x4,
	.system_soft_reset = 0x1,
};

static const struct of_device_id of_system_controller_table[] = {
	{
		.compatible = "marvell,orion-system-controller",
		.data = (void *) &orion_system_controller,
	}, {
		.compatible = "marvell,armada-370-xp-system-controller",
		.data = (void *) &armada_370_xp_system_controller,
	}, {
		.compatible = "marvell,armada-375-system-controller",
		.data = (void *) &armada_375_system_controller,
	},
	{ /* end of list */ },
};

static u32 rst_gpio = 0;
static u32 rst_invt = 0;
static u32 wdog_gpio = 0;
static u32 wdog_invt = 0;

void mvebu_restart(enum reboot_mode mode, const char *cmd)
{
	void __iomem *gpio_out_en_addr;
	void __iomem *gpio_out_data_addr;
	u32 out_en = 0;
	u32 out_data = 0;
	u32 pin = 0;
	
	if (!system_controller_base) {
		pr_err("Cannot restart, system-controller not available: check the device tree\n");
	} else {
#if 0
		/*
		 * Enable soft reset to assert RSTOUTn.
		 */
		writel(mvebu_sc->rstoutn_mask_reset_out_en,
			system_controller_base +
			mvebu_sc->rstoutn_mask_offset);
		/*
		 * Assert soft reset.
		 */
		writel(mvebu_sc->system_soft_reset,
			system_controller_base +
			mvebu_sc->system_soft_reset_offset);
#endif
		/*watchdog enable, no feeding*/
		if(wdog_gpio>=32)
		{
			gpio_out_en_addr = ioremap(system_controller_phys_base-SYSTEM_CONTROLLER_OFFSET+GPIO_MPP32_DATA_OUT_EN_OFFSET,sizeof(u32));
			gpio_out_data_addr = ioremap(system_controller_phys_base-SYSTEM_CONTROLLER_OFFSET+GPIO_MPP32_DATA_OUT_OFFSET,sizeof(u32));	
			pin = wdog_gpio-32;
		}
		else
		{
			gpio_out_en_addr = ioremap(system_controller_phys_base-SYSTEM_CONTROLLER_OFFSET+GPIO_MPP_DATA_OUT_EN_OFFSET,sizeof(u32));
			gpio_out_data_addr = ioremap(system_controller_phys_base-SYSTEM_CONTROLLER_OFFSET+GPIO_MPP_DATA_OUT_OFFSET,sizeof(u32));
			pin = wdog_gpio;
		}
		out_en = readl(gpio_out_en_addr);
		out_data = readl(gpio_out_data_addr);
		if ( ~out_en & (1<<pin) )
		{
			wdog_invt?(out_data &= ~(1<<pin)):(out_data |= (1<<pin));
		}
		writel(out_data,gpio_out_data_addr);
		
		/*soft reset*/
		out_en = 0;
		out_data = 0;
		pin = 0;
		if(rst_gpio>=32)
		{
			gpio_out_en_addr = ioremap(system_controller_phys_base-SYSTEM_CONTROLLER_OFFSET+GPIO_MPP32_DATA_OUT_EN_OFFSET,sizeof(u32));
			gpio_out_data_addr = ioremap(system_controller_phys_base-SYSTEM_CONTROLLER_OFFSET+GPIO_MPP32_DATA_OUT_OFFSET,sizeof(u32));	
			pin = rst_gpio-32;
		}
		else
		{
			gpio_out_en_addr = ioremap(system_controller_phys_base-SYSTEM_CONTROLLER_OFFSET+GPIO_MPP_DATA_OUT_EN_OFFSET,sizeof(u32));
			gpio_out_data_addr = ioremap(system_controller_phys_base-SYSTEM_CONTROLLER_OFFSET+GPIO_MPP_DATA_OUT_OFFSET,sizeof(u32));
			pin = rst_gpio;
		}
		/*use gpio to reset the whole system*/
		out_en = readl(gpio_out_en_addr);
		out_data = readl(gpio_out_data_addr);
		if ( ~out_en & (1<<pin) )
		{
			rst_invt?(out_data &= ~(1<<pin)):(out_data |= (1<<pin));
		}
		writel(out_data,gpio_out_data_addr);
	}

	while (1)
		;
}

int mvebu_system_controller_get_soc_id(u32 *dev, u32 *rev)
{
	if (of_machine_is_compatible("marvell,armada380") &&
		system_controller_base) {
		*dev = readl(system_controller_base + mvebu_sc->dev_id) >> 16;
		*rev = (readl(system_controller_base + mvebu_sc->rev_id) >> 8)
			& 0xF;
		return 0;
	} else
		return -ENODEV;
}

#if defined(CONFIG_SMP) && defined(CONFIG_MACH_MVEBU_V7)
void mvebu_armada375_smp_wa_init(void)
{
	u32 dev, rev;
	phys_addr_t resume_addr_reg;

	if (mvebu_get_soc_id(&dev, &rev) != 0)
		return;

	if (rev != ARMADA_375_Z1_REV)
		return;

	resume_addr_reg = system_controller_phys_base +
		mvebu_sc->resume_boot_addr;
	mvebu_setup_boot_addr_wa(ARMADA_375_CRYPT0_ENG_TARGET,
				 ARMADA_375_CRYPT0_ENG_ATTR,
				 resume_addr_reg);
}

void mvebu_system_controller_set_cpu_boot_addr(void *boot_addr)
{
	BUG_ON(system_controller_base == NULL);
	BUG_ON(mvebu_sc->resume_boot_addr == 0);

	if (of_machine_is_compatible("marvell,armada375"))
		mvebu_armada375_smp_wa_init();

	writel(virt_to_phys(boot_addr), system_controller_base +
	       mvebu_sc->resume_boot_addr);
}
#endif

static int __init mvebu_system_controller_init(void)
{
	const struct of_device_id *match;
	struct device_node *np;

	np = of_find_matching_node_and_match(NULL, of_system_controller_table,
					     &match);
	if (np) {
		struct resource res;
		system_controller_base = of_iomap(np, 0);
		of_address_to_resource(np, 0, &res);
		system_controller_phys_base = res.start;
		mvebu_sc = (struct mvebu_system_controller *)match->data;
		of_node_put(np);
		of_property_read_u32(np,"rst-gpio",&rst_gpio);
		of_property_read_u32(np,"rst-invt",&rst_invt);
		of_property_read_u32(np,"wdog-gpio",&wdog_gpio);
		of_property_read_u32(np,"wdog-invt",&wdog_invt);
	}

	return 0;
}

early_initcall(mvebu_system_controller_init);
