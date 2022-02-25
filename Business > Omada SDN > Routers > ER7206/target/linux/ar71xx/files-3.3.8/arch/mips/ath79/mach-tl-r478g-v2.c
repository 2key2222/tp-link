/*
 *  TP-LINK TL-R478GV2 board support
 *
 *  Copyright (C) 2015-2016 chenqiang 
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License version 2 as published
 *  by the Free Software Foundation.
 */

#include <linux/pci.h>
#include <linux/phy.h>
#include <linux/platform_device.h>
#include <linux/ath9k_platform.h>
#include <linux/ar8216_platform.h>

#include <asm/mach-ath79/ar71xx_regs.h>

#include "common.h"
#include "pci.h"
#include "dev-usb.h"
#include "dev-eth.h"
#include "dev-gpio-buttons.h"
#include "dev-leds-gpio.h"
#include "dev-m25p80.h"
#include "dev-spi.h"
#include "dev-wmac.h"
#include "machtypes.h"

#define TL_R478GV2_GPIO_BTN_RESET	10
#define TL_R478GV2_GPIO_BTN_LED_ENABLE	1

#define TL_R478GV2_GPIO_LED_SYSTEM	9

#define TL_R478GV2_KEYS_POLL_INTERVAL		20	/* msecs */
#define TL_R478GV2_KEYS_DEBOUNCE_INTERVAL	(3 * TL_R478GV2_KEYS_POLL_INTERVAL)


static const char *tl_r478gv2_part_probes[] = {
	"tp-link",
	NULL,
};

static struct flash_platform_data tl_r478gv2_flash_data = {
	.part_probes	= tl_r478gv2_part_probes,
};

static struct gpio_led tl_r478gv2_leds_gpio[] __initdata = {
	{
		.name		= "SYS_LED",
		.gpio		= TL_R478GV2_GPIO_LED_SYSTEM,
		.active_low	= 1,
	}, 
	{
		.name		= "LED_ENABLE",
		.gpio		= TL_R478GV2_GPIO_BTN_LED_ENABLE,
		.active_low	= 1,
	},
};

static struct gpio_keys_button tl_r478gv2_gpio_keys[] __initdata = {
	{
		.desc		= "reset",
		.type		= EV_KEY,
		.code		= KEY_RESTART,
		.debounce_interval = TL_R478GV2_KEYS_DEBOUNCE_INTERVAL,
		.gpio		= TL_R478GV2_GPIO_BTN_RESET,
		.active_low	= 1,
	}
};

#if 0
/* GMAC0 of the AR8327 switch is connected to the QCA9558 SoC via SGMII */
static struct ar8327_pad_cfg r478gv2_ar8327_pad0_cfg = {
	.mode = AR8327_PAD_MAC_SGMII,
	.sgmii_txclk_phase_sel = AR8327_SGMII_CLK_PHASE_RISE,
	.sgmii_rxclk_phase_sel = AR8327_SGMII_CLK_PHASE_FALL,
};

static struct ar8327_led_cfg r478gv2_ar8327_led_cfg = {
	.led_ctrl0 = 0xC335C335, 	
	.led_ctrl1 = 0xCC35CC35,
	.led_ctrl2 = 0x08010801,
	.led_ctrl3 = 0x00F3CF00,
	.open_drain = false,		//driver mode, PWS_REG(Address:0x10, bit:24)
};

static struct ar8327_platform_data r478gv2_ar8327_data = {
	.pad0_cfg = &r478gv2_ar8327_pad0_cfg,	
	.cpuport_cfg = {
		.force_link = 1,
		.speed = AR8327_PORT_SPEED_1000,
		.duplex = 1,
		.txpause = 1,
		.rxpause = 1,
	},

	
	.led_cfg = &r478gv2_ar8327_led_cfg,
};

static struct mdio_board_info r478gv2_mdio0_info[] = {
	{
		.bus_id = "ag71xx-mdio.0",
		.phy_addr = 0,
		.platform_data = &r478gv2_ar8327_data,
	},
};
#endif

static void __init tl_r478gv2_setup(void)
{

	ath79_register_m25p80(&tl_r478gv2_flash_data);

	ath79_register_leds_gpio(-1, ARRAY_SIZE(tl_r478gv2_leds_gpio),
				 tl_r478gv2_leds_gpio);
	ath79_register_gpio_keys_polled(-1, TL_R478GV2_KEYS_POLL_INTERVAL,
					 ARRAY_SIZE(tl_r478gv2_gpio_keys),
					 tl_r478gv2_gpio_keys);

	/*mdiobus_register_board_info(r478gv2_mdio0_info,
				    ARRAY_SIZE(r478gv2_mdio0_info));

	ath79_register_mdio(0, 0x0);*/

	/* GMAC0 is connected to an AR8327 switch by RGMII interface */
	/*ath79_eth0_data.phy_if_mode = PHY_INTERFACE_MODE_SGMII;
	ath79_eth0_data.phy_mask = BIT(0);
	ath79_eth0_data.mii_bus_dev = &ath79_mdio0_device.dev;
	ath79_eth0_pll_data.pll_1000 = 0x56000000;

	athrs_sgmii_res_cal();
	
	ath79_init_mac(ath79_eth0_data.mac_addr, NULL, 0);
	ath79_register_eth(0);*/
}

MIPS_MACHINE(ATH79_MACH_TL_R478GV2, "TL-R478GV2",
	     "TP-LINK R478GV2", tl_r478gv2_setup);
