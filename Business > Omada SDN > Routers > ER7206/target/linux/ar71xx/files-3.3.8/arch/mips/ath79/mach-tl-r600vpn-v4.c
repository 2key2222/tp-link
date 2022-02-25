/*
 *  TP-LINK TL-R600VPN_V4 board support
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

#define TL_R600VPN_V4_GPIO_BTN_RESET              10

#define TL_R600VPN_V4_GPIO_LED_ENABLE             5
#define TL_R600VPN_V4_GPIO_LED_SYSTEM             1

#define TL_R600VPN_V4_KEYS_POLL_INTERVAL          20      /* msecs */
#define TL_R600VPN_V4_KEYS_DEBOUNCE_INTERVAL      (3 * TL_R600VPN_V4_KEYS_POLL_INTERVAL)


static const char *tl_r600vpn_v4_part_probes[] = {
        "tp-link",
        NULL,
};

static struct flash_platform_data tl_r600vpn_v4_flash_data = {
        .part_probes    = tl_r600vpn_v4_part_probes,
};

static struct gpio_led tl_r600vpn_v4_leds_gpio[] __initdata = {
        {
                .name           = "SYS_LED",
                .gpio           = TL_R600VPN_V4_GPIO_LED_SYSTEM,
                .active_low     = 0,
        }, {
                .name           = "LED_ENABLE",
                .gpio           = TL_R600VPN_V4_GPIO_LED_ENABLE,
                .active_low     = 1,
                .default_state  = LEDS_GPIO_DEFSTATE_ON,
        },
};

static struct gpio_keys_button tl_r600vpn_v4_gpio_keys[] __initdata = {
        {
                .desc           = "reset",
                .type           = EV_KEY,
                .code           = KEY_RESTART,
                .debounce_interval = TL_R600VPN_V4_KEYS_DEBOUNCE_INTERVAL,
                .gpio           = TL_R600VPN_V4_GPIO_BTN_RESET,
                .active_low     = 1,
        }
};

/* GMAC0 of the AR8327 switch is connected to the QCA9558 SoC via SGMII */
static struct ar8327_pad_cfg r600vpn_v4_ar8327_pad0_cfg = {
        .mode = AR8327_PAD_MAC_SGMII,
        .sgmii_txclk_phase_sel = AR8327_SGMII_CLK_PHASE_RISE,
        .sgmii_rxclk_phase_sel = AR8327_SGMII_CLK_PHASE_FALL,
};


static struct ar8327_led_cfg r600vpn_v4_ar8327_led_cfg = {
        .led_ctrl0 = 0xCC35CC35,        
        .led_ctrl1 = 0xC335C335,        
        .led_ctrl2 = 0x08010801,
        .led_ctrl3 = 0x00F3CF00,
        .open_drain = false,            //driver mode, PWS_REG(Address:0x10, bit:24)
};

static struct ar8327_platform_data r600vpn_v4_ar8327_data = {
        .pad0_cfg = &r600vpn_v4_ar8327_pad0_cfg,
        .cpuport_cfg = {
                .force_link = 1,
                .speed = AR8327_PORT_SPEED_1000,
                .duplex = 1,
                .txpause = 1,
                .rxpause = 1,
        },

        .led_cfg = &r600vpn_v4_ar8327_led_cfg,
};

static struct mdio_board_info r600vpn_v4_mdio0_info[] = {
        {
                .bus_id = "ag71xx-mdio.0",
                .phy_addr = 0,
                .platform_data = &r600vpn_v4_ar8327_data,
        },
};

#define R600VPN_V4_GPIO_MDC                       3
#define R600VPN_V4_GPIO_MDIO                      4

static void __init tl_r600vpn_v4_mdio_setup(void)
{
        ath79_gpio_output_select(R600VPN_V4_GPIO_MDC, QCA956X_GPIO_OUT_MUX_GE0_MDC);
        ath79_gpio_output_select(R600VPN_V4_GPIO_MDIO, QCA956X_GPIO_OUT_MUX_GE0_MDO);

        ath79_register_mdio(0, 0x0);
}

static void __init tl_r600vpn_v4_setup(void)
{
        u8 *mac = (u8 *) KSEG1ADDR(0x1f01fc00);
        u8 *ee = (u8 *) KSEG1ADDR(0x1fff1000);

        ath79_register_m25p80(&tl_r600vpn_v4_flash_data);

        ath79_register_leds_gpio(-1, ARRAY_SIZE(tl_r600vpn_v4_leds_gpio),
                                 tl_r600vpn_v4_leds_gpio);
        ath79_register_gpio_keys_polled(-1, TL_R600VPN_V4_KEYS_POLL_INTERVAL,
                                         ARRAY_SIZE(tl_r600vpn_v4_gpio_keys),
                                         tl_r600vpn_v4_gpio_keys);

        tl_r600vpn_v4_mdio_setup();

        mdiobus_register_board_info(r600vpn_v4_mdio0_info,
                                    ARRAY_SIZE(r600vpn_v4_mdio0_info));

        ath79_register_wmac(ee, mac);
        
        ath79_register_pci();
        
        /* GMAC0 is connected to an AR8327 switch by RGMII interface */
#if 1
        ath79_eth0_data.phy_if_mode = PHY_INTERFACE_MODE_SGMII;
#ifdef CONFIG_RTL8370MB
        ath79_eth0_data.phy_mask = BIT(0)|BIT(5);
#else
        ath79_eth0_data.phy_mask = BIT(0);
#endif
        ath79_eth0_data.mii_bus_dev = &ath79_mdio0_device.dev;
        ath79_eth0_pll_data.pll_1000 = 0x56000000;

        athrs_sgmii_res_cal();
        
        ath79_init_mac(ath79_eth0_data.mac_addr, mac, 0);
        ath79_register_eth(0);
#else
        ath79_eth0_data.phy_if_mode = PHY_INTERFACE_MODE_SGMII;
        ath79_eth0_data.speed = SPEED_1000;
        ath79_eth0_data.duplex = DUPLEX_FULL;
        ath79_eth0_data.force_link = 1;


        ath79_eth0_data.phy_mask = BIT(0);
        ath79_eth0_data.mii_bus_dev = &ath79_mdio0_device.dev;

        ath79_eth0_pll_data.pll_1000 = 0x06000000;
#ifdef CONFIG_RTL8370MB
        ath79_eth0_data.phy_mask = BIT(0)|BIT(5);
#else
        ath79_eth0_data.phy_mask = BIT(0);
#endif

        athrs_sgmii_res_cal();
                
        ath79_init_mac(ath79_eth0_data.mac_addr, mac, 0);
        ath79_register_eth(0);
#endif
}

MIPS_MACHINE(ATH79_MACH_TL_R600VPN_V4, "TL-R600VPNV4",
             "TP-LINK TL-R600VPN-V4", tl_r600vpn_v4_setup);
