/*
 *  MTK common GPIO LEDs support
 *
 */

#ifndef _MTK_DEV_LEDS_GPIO_H
#define _MTK_DEV_LEDS_GPIO_H

#include <linux/leds.h>

void mtk_register_leds_gpio(int id,
			      unsigned num_leds,
			      struct gpio_led *leds);

#endif /* _MTK_DEV_LEDS_GPIO_H */
