/******************************************************************************
*
* Copyright (c) 2016 TP-LINK Technologies CO.,LTD.
* All rights reserved.
*
* FILE NAME		:   gpio.h
* VERSION		:   1.0
* DESCRIPTION	:   mt7628 gpio definations.
*
* AUTHOR		:   Wu Yin (wuyin@tp-link.net)
* CREATE DATE	:   05/13/2016
*
* HISTORY		:
* 01   05/13/2016  Wu Yin     Create.
*
******************************************************************************/

#ifndef __ASM_MACH_MTK_GPIO_H
#define __ASM_MACH_MTK_GPIO_H

#include "ralink_gpio.h"

#define ARCH_NR_GPIOS RALINK_GPIO_NUMBER
#include <asm-generic/gpio.h>

int gpio_to_irq(unsigned gpio);
int irq_to_gpio(unsigned irq);
int gpio_get_value(unsigned gpio);
void gpio_set_value(unsigned gpio, int value);
int mt7628_gpio_direction_output(unsigned gpio, int value);
int mt7628_gpio_direction_input(unsigned gpio);
int gpio_direction_select(unsigned gpio, int output);

#define gpio_cansleep	__gpio_cansleep

#endif
