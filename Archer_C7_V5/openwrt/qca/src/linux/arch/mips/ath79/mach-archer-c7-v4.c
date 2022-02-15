
/*
 * Atheros AP152 reference board support
 *
 * Copyright (c) 2014 The Linux Foundation. All rights reserved.
 * Copyright (c) 2012 Gabor Juhos <juhosg@openwrt.org>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

#include <linux/platform_device.h>
#include <linux/ath9k_platform.h>
#include <linux/ar8216_platform.h>
#include <linux/proc_fs.h>
#include <linux/delay.h>

#include <asm/mach-ath79/ar71xx_regs.h>

#include "common.h"
#include "dev-m25p80.h"
#include "machtypes.h"
#include "pci.h"
#include "dev-eth.h"
#include "dev-gpio-buttons.h"
#include "dev-leds-gpio.h"
#include "dev-spi.h"
#include "dev-usb.h"
#include "dev-wmac.h"

extern void gpio_set_value(unsigned gpio, int value);

static struct proc_dir_entry *shift_register_entry = NULL;
uint32_t shift_register_data = 0xff;


#define SHIFT_REG_TW_FACTOR	                120
#define SHIFT_REG_SER_SRCLK_DELAY_FACTOR	150
#define SHIFT_REG_SRCLR_RCLK_DELAY_FACTOR	80


#define AP152_SHIFT_REGISTER_NAME "shift_register"

#define AP152_GPIO_BTN_RESET            5
#define AP152_GPIO_BTN_WPS_WIFI         2

#define AP152_GPIO_LED_WLAN_5G          9
#define AP152_GPIO_LED_STATUS           6
#define AP152_GPIO_LED_USB1             7
#define AP152_GPIO_LED_USB2             8

#define AP152_GPIO_SHIFT_OE     1
#define AP152_GPIO_SHIFT_SER    14
#define AP152_GPIO_SHIFT_SRCLK  15
#define AP152_GPIO_SHIFT_RCLK   16
#define AP152_GPIO_USB1_ENABLE  19
#define AP152_GPIO_USB2_ENABLE  20
#define AP152_GPIO_SHIFT_SRCLR  21

#define AP152_KEYS_POLL_INTERVAL        20     /* msecs */
#define AP152_KEYS_DEBOUNCE_INTERVAL    (3 * AP152_KEYS_POLL_INTERVAL)

#define AP152_MAC0_OFFSET               0
#define AP152_MAC1_OFFSET               6
#define AP152_WMAC_CALDATA_OFFSET       0x1000

#define AP152_GPIO_MDC			3
#define AP152_GPIO_MDIO			4

enum SHIFT_REGISTER_OUTPUT {
    Q7_2G_WIFI_LED = 0,
    Q6_WAN_OLED,
    Q5_WAN_GLED,
    Q4_LAN1_LED,
    Q3_LAN2_LED,
    Q2_LAN3_LED,
    Q1_LAN4_LED,
    Q0_WPS_LED,
    SHIFT_REGISTER_OUTPUT_NUM
};

static struct gpio_led ap152_leds_gpio[] __initdata = {
	/*{
		.name		= "ap152:green:usb0",
		.gpio		= AP152_GPIO_LED_USB0,
		.active_low	= 1,
	},
	{
		.name		= "ap152:green:usb1",
		.gpio		= AP152_GPIO_LED_USB1,
		.active_low	= 1,
	},*/
	{
		.name		= "usb_1",
		.gpio		= AP152_GPIO_LED_USB1,
		.active_low	= 1,
	},
	{
		.name		= "usb_2",
		.gpio		= AP152_GPIO_LED_USB2,
		.active_low	= 1,
	},
	{
		.name		= "wifi_5g",
		.gpio		= AP152_GPIO_LED_WLAN_5G,
		.active_low	= 1,
	},
	{
		.name		= "status",
		.gpio		= AP152_GPIO_LED_STATUS,
		.active_low	= 1,
		.default_state = LEDS_GPIO_DEFSTATE_ON,
	},
};

static struct gpio_keys_button ap152_gpio_keys[] __initdata = {
        {
                .desc           = "WPS and WIFI button",
                .type           = EV_KEY,
                .code           = KEY_WPS_BUTTON,
                .debounce_interval = AP152_KEYS_DEBOUNCE_INTERVAL,
                .gpio           = AP152_GPIO_BTN_WPS_WIFI,
                .active_low     = 1,
        },
        {
                .desc           = "Reset button",
                .type           = EV_KEY,
                .code           = KEY_RESTART,
                .debounce_interval = AP152_KEYS_DEBOUNCE_INTERVAL,
                .gpio           = AP152_GPIO_BTN_RESET,
                .active_low     = 1,
        },
};

static void shift_register_set(u_int32_t val) 
{
    int index = 0;
	int value = 0;
    
	gpio_set_value(AP152_GPIO_SHIFT_RCLK, 0);
	
	for(index = 0; index < SHIFT_REGISTER_OUTPUT_NUM; index++)
	{
		value = (val >> index) & 0x1;
        gpio_set_value(AP152_GPIO_SHIFT_SER, value);
        ndelay(SHIFT_REG_SER_SRCLK_DELAY_FACTOR);
		gpio_set_value(AP152_GPIO_SHIFT_SRCLK, 1);
		ndelay(SHIFT_REG_TW_FACTOR);
		gpio_set_value(AP152_GPIO_SHIFT_SRCLK, 0);
	}

	gpio_set_value(AP152_GPIO_SHIFT_RCLK, 1);
    ndelay(SHIFT_REG_TW_FACTOR);
	gpio_set_value(AP152_GPIO_SHIFT_RCLK, 0);
	ndelay(SHIFT_REG_TW_FACTOR);
}

static int shift_register_proc_read(char *page, char **start, off_t off,
                               int count, int *eof, void *data)
{
    return sprintf (page, "%u\n", shift_register_data);
}

static int shift_register_proc_write(struct file *file, const char *buf,
                                        unsigned long count, void *data)
{
    u_int32_t val = 0;

    if (sscanf(buf, "%u", &val) != 1)
    {
        return -EINVAL;
    }

    if ((val < 0) || (val > 0xff))
    {
        return -EINVAL;
    }

	if(val != shift_register_data)
	{
	    shift_register_set(val);
	}
    shift_register_data = val;


    return count;
}


static void __init ap152_shift_register_setup(void)
{
#if 0
    gpio_set_value(AP152_GPIO_SHIFT_OE, 1);
	gpio_set_value(AP152_GPIO_SHIFT_SER, 0);
	gpio_set_value(AP152_GPIO_SHIFT_SRCLK, 0);
	gpio_set_value(AP152_GPIO_SHIFT_SRCLR, 0);
	gpio_set_value(AP152_GPIO_SHIFT_RCLK, 0);
	
	ath79_gpio_direction_select(AP152_GPIO_SHIFT_OE, true);
	ath79_gpio_direction_select(AP152_GPIO_SHIFT_SER, true);
	ath79_gpio_direction_select(AP152_GPIO_SHIFT_SRCLK, true);
	ath79_gpio_direction_select(AP152_GPIO_SHIFT_SRCLR, true);
	ath79_gpio_direction_select(AP152_GPIO_SHIFT_RCLK, true);
	
    /*clear shift register*/
	

	
	ndelay(SHIFT_REG_TW_FACTOR);
	gpio_set_value(AP152_GPIO_SHIFT_SRCLR, 1);
	ndelay(SHIFT_REG_SRCLR_RCLK_DELAY_FACTOR);

    shift_register_set(shift_register_data);
    
    printk("reset hub\n");
	
	ndelay(1000);
	shift_register_data |= 1<< QH_HUB_RESET;
	shift_register_set(shift_register_data);
#endif
    gpio_set_value(AP152_GPIO_SHIFT_OE, 0);

    /*leo test usb enable,20170412*/
    gpio_set_value(AP152_GPIO_USB1_ENABLE, 0);
    gpio_set_value(AP152_GPIO_USB2_ENABLE, 0);
  
}


static void __init ap152_proc_setup(void)
{
	shift_register_entry = create_proc_entry (AP152_SHIFT_REGISTER_NAME, 0644, NULL);
    if (!shift_register_entry)
    {
        printk("Error: Can not create /proc/%s\n", AP152_SHIFT_REGISTER_NAME);
        return;
    }

    shift_register_entry->write_proc = shift_register_proc_write;
    shift_register_entry->read_proc = shift_register_proc_read;    
}

static struct ar8327_pad_cfg ap152_ar8337_pad0_cfg = {
	.mode = AR8327_PAD_MAC_SGMII,
	.sgmii_txclk_phase_sel = AR8327_SGMII_CLK_PHASE_RISE,
	.sgmii_rxclk_phase_sel = AR8327_SGMII_CLK_PHASE_FALL,
};

static struct ar8327_platform_data ap152_ar8337_data = {
	.pad0_cfg = &ap152_ar8337_pad0_cfg,
	.cpuport_cfg = {
		.force_link = 1,
		.speed = AR8327_PORT_SPEED_1000,
		.duplex = 1,
		.txpause = 1,
		.rxpause = 1,
	},
};

static struct mdio_board_info ap152_mdio0_info[] = {
	{
		.bus_id = "ag71xx-mdio.0",
		.phy_addr = 0,
		.platform_data = &ap152_ar8337_data,
	},
};

static void __init ap152_mdio_setup(void)
{
	ath79_gpio_output_select(AP152_GPIO_MDC, QCA956X_GPIO_OUT_MUX_GE0_MDC);
	ath79_gpio_output_select(AP152_GPIO_MDIO, QCA956X_GPIO_OUT_MUX_GE0_MDO);

	ath79_register_mdio(0, 0x0);
}

static void __init archer_c7_v4_setup(void)
{
	u8 *art = (u8 *) KSEG1ADDR(0x1fff0000);

	ath79_register_m25p80(NULL);

	ath79_register_leds_gpio(-1, ARRAY_SIZE(ap152_leds_gpio),
							ap152_leds_gpio);
	ath79_register_gpio_keys_polled(-1, AP152_KEYS_POLL_INTERVAL,
									ARRAY_SIZE(ap152_gpio_keys),
									ap152_gpio_keys);

	ap152_shift_register_setup();

	ath79_register_usb();

	ap152_mdio_setup();

	mdiobus_register_board_info(ap152_mdio0_info,
								ARRAY_SIZE(ap152_mdio0_info));

	ath79_register_wmac(art + AP152_WMAC_CALDATA_OFFSET, NULL);
	ath79_register_pci();

	/* GMAC0 is connected to an AR8337 switch */
	ath79_init_mac(ath79_eth0_data.mac_addr, art + AP152_MAC0_OFFSET, 0);
	ath79_eth0_data.phy_if_mode = PHY_INTERFACE_MODE_SGMII;
	ath79_eth0_data.speed = SPEED_1000;
	ath79_eth0_data.duplex = DUPLEX_FULL;
	ath79_eth0_data.phy_mask = BIT(0);
	ath79_eth0_data.force_link = 1;
	ath79_eth0_data.mii_bus_dev = &ath79_mdio0_device.dev;
	ath79_eth0_pll_data.pll_1000 = 0x06000000;
	ath79_register_eth(0);

	ap152_proc_setup();
}

MIPS_MACHINE(ATH79_MACH_ARCHER_C7_V4, "AP152", "TP-LINK ARCHER C7 v4 support",
	     archer_c7_v4_setup);
