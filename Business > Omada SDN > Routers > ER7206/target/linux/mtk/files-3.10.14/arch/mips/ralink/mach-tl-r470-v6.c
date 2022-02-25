#include <linux/platform_device.h>

#include <asm/delay.h>

#include "dev-gpio-buttons.h"
#include "dev-leds-gpio.h"

#define TL_R470_V6_GPIO_BTN_RESET	       	38
#define TL_R470_V6_GPIO_LED_SYSTEM	       	11
#define TL_R470_V6_KEYS_POLL_INTERVAL		20	/* msecs */
#define TL_R470_V6_KEYS_DEBOUNCE_INTERVAL 	(3 * TL_R470_V6_KEYS_POLL_INTERVAL)

static struct gpio_led tl_r470_v6_leds_gpio[] __initdata = {
	{
		.name		= "SYS_LED",
		.gpio		= TL_R470_V6_GPIO_LED_SYSTEM,
		.active_low	= 0,
	}
};

static struct gpio_keys_button tl_r470_v6_gpio_keys[] __initdata = {
	{
		.desc		= "reset",
		.type		= EV_KEY,
		.code		= KEY_RESTART,
		.debounce_interval = TL_R470_V6_KEYS_DEBOUNCE_INTERVAL,
		.gpio		= TL_R470_V6_GPIO_BTN_RESET,
		.active_low	= 1,
	}
};

void self_delay(void)
{
    int i = 0x7fffffff;
    while (i > 0)
        i --;
}

void gpio_set_value(unsigned gpio, int value);
static int __init tl_r470_v6_setup(void)
{
    mtk_register_leds_gpio(-1, ARRAY_SIZE(tl_r470_v6_leds_gpio),
				 tl_r470_v6_leds_gpio);
	mtk_register_gpio_keys_polled(-1, TL_R470_V6_KEYS_POLL_INTERVAL,
					 ARRAY_SIZE(tl_r470_v6_gpio_keys),
					 tl_r470_v6_gpio_keys);
					 
	return 0;
}

arch_initcall(tl_r470_v6_setup);
