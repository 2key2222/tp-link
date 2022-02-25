/*
 *  TP-LINK TL-WVR450G board support
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
#include "dev-ap9x-pci.h"
#include "dev-eth.h"
#include "dev-gpio-buttons.h"
#include "dev-leds-gpio.h"
#include "dev-m25p80.h"
#include "dev-spi.h"
#include "dev-wmac.h"
#include "machtypes.h"

#define TL_WVR450G_GPIO_BTN_RESET	16
#define TL_WVR450G_GPIO_BTN_WLAN	17
#define TL_WVR450G_GPIO_LED_WPS		18
#define TL_WVR450G_GPIO_LED_WLAN		12

#define TL_WVR450G_GPIO_LED_SYSTEM	14
#define TL_WVR450G_GPIO_LED_USB		19

#define TL_WVR450G_KEYS_POLL_INTERVAL		20	/* msecs */
#define TL_WVR450G_KEYS_DEBOUNCE_INTERVAL	(3 * TL_WVR450G_KEYS_POLL_INTERVAL)

#define TL_WVR450G_PCIE_CALDATA_OFFSET	0x5000

static const char *tl_wvr450g_part_probes[] = {
	"tp-link",
	NULL,
};

static struct flash_platform_data tl_wvr450g_flash_data = {
	.part_probes	= tl_wvr450g_part_probes,
};

static struct gpio_led tl_wvr450g_leds_gpio[] __initdata = {
	{
		.name		= "tp-link:green:system",
		.gpio		= TL_WVR450G_GPIO_LED_SYSTEM,
		.active_low	= 1,
	}, {
		.name		= "tp-link:green:wps",
		.gpio		= TL_WVR450G_GPIO_LED_WPS,
		.active_low	= 1,
	}, {
		.name		= "tp-link:green:wlan",
		.gpio		= TL_WVR450G_GPIO_LED_WLAN,
		.active_low	= 1,
	}, {
		.name		= "tp-link:green:usb",
		.gpio		= TL_WVR450G_GPIO_LED_USB,
		.active_low	= 1,
	},
};

static struct gpio_keys_button tl_wvr450g_gpio_keys[] __initdata = {
	{
		.desc		= "reset",
		.type		= EV_KEY,
		.code		= KEY_RESTART,
		.debounce_interval = TL_WVR450G_KEYS_DEBOUNCE_INTERVAL,
		.gpio		= TL_WVR450G_GPIO_BTN_RESET,
		.active_low	= 1,
	}
};

/* GMAC0 of the AR8327 switch is connected to the QCA9558 SoC via SGMII */
static struct ar8327_pad_cfg wvr450g_ar8327_pad0_cfg = {
	.mode = AR8327_PAD_MAC_SGMII,
	//.sgmii_txclk_phase_sel = AR8327_SGMII_CLK_PHASE_RISE,
	//.sgmii_rxclk_phase_sel = AR8327_SGMII_CLK_PHASE_FALL,
};

/* GMAC6 of the AR8327 switch is connected to the QCA9558 SoC via RGMII */
static struct ar8327_pad_cfg wvr450g_ar8327_pad6_cfg = {
	.mode = AR8327_PAD_MAC_RGMII,
	.txclk_delay_en = true,
	.rxclk_delay_en = true,
	.txclk_delay_sel = AR8327_CLK_DELAY_SEL1,
	.rxclk_delay_sel = AR8327_CLK_DELAY_SEL2,
};

static struct ar8327_led_cfg wvr450g_ar8327_led_cfg = {
	.led_ctrl0 = 0xcc05cc05, 	//right green link with 1000Mb
	.led_ctrl1 = 0xca05ca05,	//right yellow link with 100Mb
	.led_ctrl2 = 0xcf36cf36,	//link and act, blink at 8Hz when rx/tx packet
	.led_ctrl3 = 0x03ffff03,
	.open_drain = false,		//driver mode, PWS_REG(Address:0x10, bit:24)
};

static struct ar8327_platform_data wvr450g_ar8327_data = {
	.pad0_cfg = &wvr450g_ar8327_pad0_cfg,	
	.pad6_cfg = &wvr450g_ar8327_pad6_cfg,
	.cpuport_cfg = {
		.force_link = 1,
		.speed = AR8327_PORT_SPEED_1000,
		.duplex = 1,
		.txpause = 1,
		.rxpause = 1,
	},
	.port6_cfg = {
		.force_link = 1,
		.speed = AR8327_PORT_SPEED_1000,
		.duplex = 1,
		.txpause = 1,
		.rxpause = 1,
	},
	
	.led_cfg = &wvr450g_ar8327_led_cfg,
};

static struct mdio_board_info wvr450g_mdio0_info[] = {
	{
		.bus_id = "ag71xx-mdio.0",
		.phy_addr = 0,
		.platform_data = &wvr450g_ar8327_data,
	},
};

static void __init tl_wvr450g_setup(void)
{
	u8 *mac = (u8 *) KSEG1ADDR(0x1f01fc00);
	u8 *ee = (u8 *) KSEG1ADDR(0x1fff1000);

	ath79_register_m25p80(&tl_wvr450g_flash_data);

	ath79_register_leds_gpio(-1, ARRAY_SIZE(tl_wvr450g_leds_gpio),
				 tl_wvr450g_leds_gpio);
	ath79_register_gpio_keys_polled(-1, TL_WVR450G_KEYS_POLL_INTERVAL,
					 ARRAY_SIZE(tl_wvr450g_gpio_keys),
					 tl_wvr450g_gpio_keys);
	ath79_register_wmac(ee, mac);

	mdiobus_register_board_info(wvr450g_mdio0_info,
				    ARRAY_SIZE(wvr450g_mdio0_info));

	ath79_register_mdio(1, 0x0);
	ath79_register_mdio(0, 0x0);
	
	ath79_setup_qca955x_eth_cfg(QCA955X_ETH_CFG_RGMII_EN);
	

	/* GMAC0 is connected to an AR8327 switch by RGMII interface */
	ath79_eth0_data.phy_if_mode = PHY_INTERFACE_MODE_RGMII;
	ath79_eth0_data.phy_mask = BIT(0);
	ath79_eth0_data.mii_bus_dev = &ath79_mdio0_device.dev;
	ath79_eth0_pll_data.pll_1000 = 0x56000000;

	ath79_init_mac(ath79_eth0_data.mac_addr, mac, 1);
	ath79_register_eth(0);


	/* GMAC1 is connected to an AR8327 switch by SGMII interface */
	ath79_eth1_data.phy_if_mode = PHY_INTERFACE_MODE_SGMII;
	ath79_eth1_data.speed = SPEED_1000;
	ath79_eth1_data.duplex = DUPLEX_FULL;
	ath79_eth1_pll_data.pll_1000 = 0x03000101;

	ath79_init_mac(ath79_eth1_data.mac_addr, mac, 0);
	ath79_register_eth(1);


}

MIPS_MACHINE(ATH79_MACH_TL_WVR450G, "TL-WVR450G",
	     "TP-LINK TL-WVR450G", tl_wvr450g_setup);
