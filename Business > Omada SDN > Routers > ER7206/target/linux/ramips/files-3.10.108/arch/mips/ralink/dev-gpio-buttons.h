/*
 *  MTK GPIO button support
 *
 */

#ifndef _MTK_DEV_GPIO_BUTTONS_H
#define _MTK_DEV_GPIO_BUTTONS_H

#include <linux/input.h>
#include <linux/gpio_keys.h>

void mtk_register_gpio_keys_polled(int id,
				     unsigned poll_interval,
				     unsigned nbuttons,
				     struct gpio_keys_button *buttons);

#endif /* _MTK_DEV_GPIO_BUTTONS_H */
