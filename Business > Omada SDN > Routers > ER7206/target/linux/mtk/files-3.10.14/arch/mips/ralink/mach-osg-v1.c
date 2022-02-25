#include <linux/platform_device.h>

#include <asm/delay.h>
#include <asm/rt2880/rt_mmap.h>

#include "dev-gpio-buttons.h"
#include "dev-leds-gpio.h"

#define PHYS_TO_K1(physaddr) KSEG1ADDR(physaddr)
#define sysRegRead(phys) (*(volatile unsigned int *)PHYS_TO_K1(phys))
#define sysRegWrite(phys, val)  ((*(volatile unsigned int *)PHYS_TO_K1(phys)) = (val))

#define OSG_V1_GPIO_BTN_RESET	       	8
#define OSG_V1_GPIO_BTN_TURBO	       	12
#define OSG_V1_GPIO_LED_SYSTEM	       	3
#define OSG_V1_GPIO_LED_TURBO	       	4
#define OSG_V1_KEYS_POLL_INTERVAL		20	/* msecs */
#define OSG_V1_KEYS_DEBOUNCE_INTERVAL 	(3 * OSG_V1_KEYS_POLL_INTERVAL)
#define OSG_V1_GPIO_LED_USB           15

#define KEY_TURBO               0x2e8

#if 1
static struct gpio_led osg_v1_leds_gpio[] __initdata = {
	{
		.name		= "SYS_LED",
		.gpio		= OSG_V1_GPIO_LED_SYSTEM,
		.active_low	= 0,
	},
	{
		.name		= "TURBO_LED",
		.gpio		= OSG_V1_GPIO_LED_TURBO,
		.active_low	= 1,
	},
	{
		.name 		= "USB_LED",
		.gpio		= OSG_V1_GPIO_LED_USB,
		.active_low	= 1,
	}
};

static struct gpio_keys_button osg_v1_gpio_keys[] __initdata = {
	{
		.desc		= "reset",
		.type		= EV_KEY,
		.code		= KEY_RESTART,
		.debounce_interval = OSG_V1_KEYS_DEBOUNCE_INTERVAL,
		.gpio		= OSG_V1_GPIO_BTN_RESET,
		.active_low	= 1,
	},
	{
		.desc		= "turbo",
		.type		= EV_KEY,
		.code		= KEY_TURBO,
		.debounce_interval = OSG_V1_KEYS_DEBOUNCE_INTERVAL,
		.gpio		= OSG_V1_GPIO_BTN_TURBO,
		.active_low	= 0,
	}
};
#endif
void self_delay(void)
{
    int i = 0x7fffffff;
    while (i > 0)
        i --;
}

void gpio_set_value(unsigned gpio, int value);
static int __init osg_v1_setup(void)
{

    u32 val=0; 
    val = sysRegRead(RALINK_SYSCTL_BASE + 0x60);
    val |= 0x00000010;
    sysRegWrite(RALINK_SYSCTL_BASE + 0x60, val);
    mtk_register_leds_gpio(-1, ARRAY_SIZE(osg_v1_leds_gpio),
				 osg_v1_leds_gpio);
	mtk_register_gpio_keys_polled(-1, OSG_V1_KEYS_POLL_INTERVAL,
					 ARRAY_SIZE(osg_v1_gpio_keys),
					 osg_v1_gpio_keys);

	return 0;
}

arch_initcall(osg_v1_setup);
