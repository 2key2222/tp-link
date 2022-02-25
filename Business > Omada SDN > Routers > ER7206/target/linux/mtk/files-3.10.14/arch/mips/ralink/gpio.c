/******************************************************************************
*
* Copyright (c) 2016 TP-LINK Technologies CO.,LTD.
* All rights reserved.
*
* FILE NAME		:   gpio.c
* VERSION		:   1.0
* DESCRIPTION	:   mt7628 gpio support.
*
* AUTHOR		:   Wu Yin (wuyin@tp-link.net)
* CREATE DATE	:   05/13/2016
*
* HISTORY		:
* 01   05/13/2016  Wu Yin     Create.
*
******************************************************************************/

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/spinlock.h>
#include <linux/gpio.h>
#include <linux/irq.h>
#include <linux/interrupt.h>

#include <asm/mach-ralink/ralink_gpio.h>
#include <asm/rt2880/surfboardint.h>

/* set a base irq number mapped to gpio, mtk now use irq number below 40 */
#define MTK_GPIO_IRQ_BASE 	80
#define RALINK_REG_PIODIR2		(RALINK_PRGIO_ADDR + 0x04)
#define RALINK_REG_PIODATA2		(RALINK_PRGIO_ADDR + 0x24)
#define RALINK_REG_PIOSET2		(RALINK_PRGIO_ADDR + 0x34)
#define RALINK_REG_PIORESET2	(RALINK_PRGIO_ADDR + 0x44)

static DEFINE_SPINLOCK(mtk_gpio_lock);

/******************************************************************************
* FUNCTION		: mtk_gpio_direction_input()
* AUTHOR		: Wu Yin (wuyin@tp-link.net)
* DESCRIPTION	: set direction input for gpio.
* INPUT			: struct gpio_chip *chip, unsigned offset
* OUTPUT		: N/A
* RETURN		: int
* OTHERS		:
******************************************************************************/
static int mtk_gpio_direction_input(struct gpio_chip *chip, unsigned offset)
{
	unsigned long flags;
	unsigned long tmp;
	
	if (WARN(!gpio_is_valid(offset), "invalid GPIO %d\n", offset))
		return -EINVAL;
	
	spin_lock_irqsave(&mtk_gpio_lock, flags);

	if (offset >= 0 && offset <= 31) {
		tmp = le32_to_cpu(*(volatile u32 *)(RALINK_REG_PIODIR));
		tmp &= ~cpu_to_le32(1 << offset);
		*(volatile u32 *)(RALINK_REG_PIODIR) = tmp;
	}
	else if (offset <= 63) {
		tmp = le32_to_cpu(*(volatile u32 *)(RALINK_REG_PIODIR2));
		tmp &= ~cpu_to_le32(1 << (offset - 32));
		*(volatile u32 *)(RALINK_REG_PIODIR2) = tmp;
	}
	else {
		tmp = le32_to_cpu(*(volatile u32 *)(RALINK_REG_PIO9564DIR));
		tmp &= ~cpu_to_le32(1 << (offset - 64));
		*(volatile u32 *)(RALINK_REG_PIO9564DIR) = tmp;
	}
	
	spin_unlock_irqrestore(&mtk_gpio_lock, flags);

	return 0;
}


/******************************************************************************
* FUNCTION		: mtk_gpio_direction_output()
* AUTHOR		: Wu Yin (wuyin@tp-link.net)
* DESCRIPTION	: set direction output for gpio.
* INPUT			: struct gpio_chip *chip, unsigned offset, int value
* OUTPUT		: N/A
* RETURN		: N/A
* OTHERS		: value is a default output value when set direction output
******************************************************************************/
static int mtk_gpio_direction_output(struct gpio_chip *chip, unsigned offset, int value)
{
	unsigned long flags;
	unsigned long tmp;
	
	if (WARN(!gpio_is_valid(offset), "invalid GPIO %d\n", offset))
		return -EINVAL;
	
	spin_lock_irqsave(&mtk_gpio_lock, flags);

	if (value)
	{
		if (offset >= 0 && offset <= 31)
		{
			tmp = le32_to_cpu(*(volatile u32 *)(RALINK_REG_PIODIR));
			tmp |= cpu_to_le32(1 << offset);
			*(volatile u32 *)(RALINK_REG_PIODIR) = tmp;
			*(volatile u32 *)(RALINK_REG_PIOSET) = cpu_to_le32(1 << offset);
		}
		else if (offset <= 63)
		{
			tmp = le32_to_cpu(*(volatile u32 *)(RALINK_REG_PIODIR2));
			tmp |= cpu_to_le32(1 << (offset - 32));
			*(volatile u32 *)(RALINK_REG_PIODIR2) = tmp;
			*(volatile u32 *)(RALINK_REG_PIOSET2) = cpu_to_le32(1 << (offset - 32));
		}
		else
		{
			tmp = le32_to_cpu(*(volatile u32 *)(RALINK_REG_PIO9564DIR));
			tmp |= cpu_to_le32(1 << (offset - 64));
			*(volatile u32 *)(RALINK_REG_PIO9564DIR) = tmp;
			*(volatile u32 *)(RALINK_REG_PIO9564SET) = cpu_to_le32(1 << (offset - 64));
		}
	}
	else
	{
		if (offset >= 0 && offset <= 31)
		{
			tmp = le32_to_cpu(*(volatile u32 *)(RALINK_REG_PIODIR));
			tmp |= cpu_to_le32(1 << offset);
			*(volatile u32 *)(RALINK_REG_PIODIR) = tmp;
			*(volatile u32 *)(RALINK_REG_PIORESET) = cpu_to_le32(1 << offset);
		}
		else if (offset <= 63)
		{
			tmp = le32_to_cpu(*(volatile u32 *)(RALINK_REG_PIODIR2));
			tmp |= cpu_to_le32(1 << (offset - 32));
			*(volatile u32 *)(RALINK_REG_PIODIR2) = tmp;
			*(volatile u32 *)(RALINK_REG_PIORESET2) = cpu_to_le32(1 << (offset - 32));
		}
		else
		{
			tmp = le32_to_cpu(*(volatile u32 *)(RALINK_REG_PIO9564DIR));
			tmp |= cpu_to_le32(1 << (offset - 64));
			*(volatile u32 *)(RALINK_REG_PIO9564DIR) = tmp;
			*(volatile u32 *)(RALINK_REG_PIO9564RESET) = cpu_to_le32(1 << (offset - 64));
		}
	}
	
	spin_unlock_irqrestore(&mtk_gpio_lock, flags);
	
	return 0;
}

static int __mtk_gpio_direction_select(unsigned offset, int output)
{
	unsigned long tmp = 0;
	unsigned long flags;
	
	if (WARN(!gpio_is_valid(offset), "invalid GPIO %d\n", offset))
		return -EINVAL;
	
	spin_lock_irqsave(&mtk_gpio_lock, flags);
	
	if (output)
	{
		if (offset >= 0 && offset <= 31)
		{
			tmp = le32_to_cpu(*(volatile u32 *)(RALINK_REG_PIODIR));
			tmp |= cpu_to_le32(1 << offset);
			*(volatile u32 *)(RALINK_REG_PIODIR) = tmp;
		}
		else if (offset <= 63)
		{
			tmp = le32_to_cpu(*(volatile u32 *)(RALINK_REG_PIODIR2));
			tmp |= cpu_to_le32(1 << (offset - 32));
			*(volatile u32 *)(RALINK_REG_PIODIR2) = tmp;
		}
	}
	else
	{
		if (offset >= 0 && offset <= 31) {
			tmp = le32_to_cpu(*(volatile u32 *)(RALINK_REG_PIODIR));
			tmp &= ~cpu_to_le32(1 << offset);
			*(volatile u32 *)(RALINK_REG_PIODIR) = tmp;
		}
		else if (offset <= 63) {
			tmp = le32_to_cpu(*(volatile u32 *)(RALINK_REG_PIODIR2));
			tmp &= ~cpu_to_le32(1 << (offset - 32));
			*(volatile u32 *)(RALINK_REG_PIODIR2) = tmp;
		}
	}
	
	spin_unlock_irqrestore(&mtk_gpio_lock, flags);
	
	return 0;
}

static int __mtk_gpio_get_value(unsigned gpio)
{
	unsigned long tmp;
	
	if (gpio >= 0 && gpio <= 31) {
		tmp = le32_to_cpu(*(volatile u32 *)(RALINK_REG_PIODATA));
		return (tmp >> gpio) & 1;
	}
	else if (gpio <= 63) {
		tmp = le32_to_cpu(*(volatile u32 *)(RALINK_REG_PIODATA2));
		return (tmp >> (gpio - 32)) & 1;
	}
	else {		
		tmp = le32_to_cpu(*(volatile u32 *)(RALINK_REG_PIO9564DATA));
		return (tmp >> (gpio - 64)) & 1;
	}
}

static void __mtk_gpio_set_value(unsigned gpio, int value)
{
	if (value)
	{
		if (gpio >= 0 && gpio <= 31)
			*(volatile u32 *)(RALINK_REG_PIOSET) = cpu_to_le32(1 << gpio);
		else if (gpio <= 63)			
			*(volatile u32 *)(RALINK_REG_PIOSET2) = cpu_to_le32(1 << (gpio - 32));
		else
			*(volatile u32 *)(RALINK_REG_PIO9564SET) = cpu_to_le32(1 << (gpio - 64));
	}
	else
	{
		if (gpio >= 0 && gpio <= 31)
			*(volatile u32 *)(RALINK_REG_PIORESET) = cpu_to_le32(1 << gpio);
		else if (gpio <= 63)
			*(volatile u32 *)(RALINK_REG_PIORESET2) = cpu_to_le32(1 << (gpio - 32));
		else			
			*(volatile u32 *)(RALINK_REG_PIO9564RESET) = cpu_to_le32(1 << (gpio - 64));
	}
}


static int mtk_gpio_get_value(struct gpio_chip *chip, unsigned offset)
{
	return __mtk_gpio_get_value(offset);
}

static void mtk_gpio_set_value(struct gpio_chip *chip, unsigned offset, int value)
{
	__mtk_gpio_set_value(offset, value);
}

struct gpio_chip mtk_gpio_chip = 
{
	.label = "mtk",
	.base = 0,
	.ngpio = RALINK_GPIO_NUMBER,
	.get = mtk_gpio_get_value,
	.set = mtk_gpio_set_value,
	.direction_input = mtk_gpio_direction_input,
	.direction_output = mtk_gpio_direction_output,
};

/******************************************************************************
* FUNCTION		: mtk_gpio_irq_type()
* AUTHOR		: Wu Yin (wuyin@tp-link.net)
* DESCRIPTION	: set irq raise type, now only egde irq type is implemented.
* INPUT			: struct irq_data *d, unsigned type
* OUTPUT		: N/A
* RETURN		: int ret
* OTHERS		:
******************************************************************************/
static int mtk_gpio_irq_type(struct irq_data *d, unsigned type)
{
	int offset = d->irq - MTK_GPIO_IRQ_BASE;
	unsigned long flags;
	unsigned long tmp;

	spin_lock_irqsave(&mtk_gpio_lock, flags);

	if (type & IRQ_TYPE_EDGE_RISING)
	{
		if (offset <= 31)
		{
			tmp = le32_to_cpu(*(volatile u32 *)(RALINK_REG_PIORENA));
			tmp |= (0x1 << offset);
			*(volatile u32 *)(RALINK_REG_PIORENA) = cpu_to_le32(tmp);
		}
		else if (offset <= 63)
		{
			tmp = le32_to_cpu(*(volatile u32 *)(RALINK_REG_PIO6332RENA));
			tmp |= (0x1 << (offset - 32));
			*(volatile u32 *)(RALINK_REG_PIO6332RENA) = cpu_to_le32(tmp);
		}
		else
		{
			tmp = le32_to_cpu(*(volatile u32 *)(RALINK_REG_PIO9564RENA));
			tmp |= (0x1 << (offset - 64));
			*(volatile u32 *)(RALINK_REG_PIO9564RENA) = cpu_to_le32(tmp);
		}
	}
	if (type & IRQ_TYPE_EDGE_FALLING)
	{
		if (offset <= 31)
		{
			tmp = le32_to_cpu(*(volatile u32 *)(RALINK_REG_PIOFENA));
			tmp |= (0x1 << offset);
			*(volatile u32 *)(RALINK_REG_PIOFENA) = cpu_to_le32(tmp);
		}
		else if (offset <= 63)
		{
			tmp = le32_to_cpu(*(volatile u32 *)(RALINK_REG_PIO6332FENA));
			tmp |= (0x1 << (offset - 32));
			*(volatile u32 *)(RALINK_REG_PIO6332FENA) = cpu_to_le32(tmp);
		}
		else
		{
			tmp = le32_to_cpu(*(volatile u32 *)(RALINK_REG_PIO9564FENA));
			tmp |= (0x1 << (offset - 64));
			*(volatile u32 *)(RALINK_REG_PIO9564FENA) = cpu_to_le32(tmp);
		}
	}

	spin_unlock_irqrestore(&mtk_gpio_lock, flags);
	return 0;
}

/******************************************************************************
* FUNCTION		: mtk_gpio_irq_enable()
* AUTHOR		: Wu Yin (wuyin@tp-link.net)
* DESCRIPTION	: this is a global function enable gpio irq, per gpio irq 
* 				  enable when set irq type regs.
* INPUT			: struct irq_data *d
* OUTPUT		: N/A
* RETURN		: N/A
* OTHERS		:
******************************************************************************/
static void mtk_gpio_irq_enable(struct irq_data *d)
{
	*(volatile u32 *)(RALINK_REG_INTENA) = cpu_to_le32(RALINK_INTCTL_PIO);
}

/******************************************************************************
* FUNCTION		: mtk_gpio_irq_disable()
* AUTHOR		: Wu Yin (wuyin@tp-link.net)
* DESCRIPTION	: a global function disable gpio irq.
* INPUT			: struct irq_data *d
* OUTPUT		: N/A
* RETURN		: N/A
* OTHERS		:
******************************************************************************/
static void mtk_gpio_irq_disable(struct irq_data *d)
{
	*(volatile u32 *)(RALINK_REG_INTDIS) = cpu_to_le32(RALINK_INTCTL_PIO);
}

static struct irq_chip mtk_gpio_irqchip = {
	.name = "GPIO",
	.irq_enable = mtk_gpio_irq_enable,
	.irq_disable = mtk_gpio_irq_disable,
	.irq_set_type = mtk_gpio_irq_type,
};

/******************************************************************************
* FUNCTION		: mtk_gpio_irq()
* AUTHOR		: Wu Yin (wuyin@tp-link.net)
* DESCRIPTION	: parent isr for gpio irq, clear irq related reg and handle nest irq
* INPUT			: int irq, void *dev
* OUTPUT		: N/A
* RETURN		: irqreturn_t
* OTHERS		:
******************************************************************************/
static irqreturn_t mtk_gpio_irq(int irq, void *dev)
{	
	int ralink_gpio_irqnum[RALINK_GPIO_NUMBER] = {0};
	u32 ralink_gpio_intp = 0;
	u32 ralink_gpio6332_intp = 0;
	u32 ralink_gpio9564_intp = 0;

	int i = 0, n = 0;
	int irq_base = MTK_GPIO_IRQ_BASE;

	ralink_gpio_intp = le32_to_cpu(*(volatile u32 *)(RALINK_REG_PIOINT));
	*(volatile u32 *)(RALINK_REG_PIOINT) = cpu_to_le32(0xFFFFFFFF);
	*(volatile u32 *)(RALINK_REG_PIOEDGE) = cpu_to_le32(0xFFFFFFFF);
	
	ralink_gpio6332_intp = le32_to_cpu(*(volatile u32 *)(RALINK_REG_PIO6332INT));
	*(volatile u32 *)(RALINK_REG_PIO6332INT) = cpu_to_le32(0xFFFFFFFF);
	*(volatile u32 *)(RALINK_REG_PIO6332EDGE) = cpu_to_le32(0xFFFFFFFF);

	ralink_gpio9564_intp = le32_to_cpu(*(volatile u32 *)(RALINK_REG_PIO9564INT));
	*(volatile u32 *)(RALINK_REG_PIO9564INT) = cpu_to_le32(0xFFFFFFFF);
	*(volatile u32 *)(RALINK_REG_PIO9564EDGE) = cpu_to_le32(0xFFFFFFFF);

	for (i = 0; i < 32; i++) {
		if (! (ralink_gpio_intp & (1 << i)))
			continue;
		ralink_gpio_irqnum[n] = i;
		n++;
		break;
	}
	for (i = 32; i < 64; i++) {
		if (! (ralink_gpio6332_intp & (1 << (i - 32))))
			continue;
		ralink_gpio_irqnum[n] = i;
		n++;
		break;
	}
	for (i = 64; i < RALINK_GPIO_NUMBER; i++) {
		if (! (ralink_gpio9564_intp & (1 << (i - 64))))
			continue;
		ralink_gpio_irqnum[n] = i;
		n++;
		break;
	}

	for (i = 0; i < n; i++)
		handle_nested_irq(irq_base + ralink_gpio_irqnum[i]);

	return IRQ_HANDLED;
}

/******************************************************************************
* FUNCTION		: mtk_gpio_irq_init()
* AUTHOR		: Wu Yin (wuyin@tp-link.net)
* DESCRIPTION	: init function for all gpio irqs.
* INPUT			: struct gpio_chip *chip
* OUTPUT		: N/A
* RETURN		: int
* OTHERS		:
******************************************************************************/
static int mtk_gpio_irq_init(struct gpio_chip *chip)
{
	int irq;
	int irq_base = MTK_GPIO_IRQ_BASE;

	for (irq = irq_base; irq < irq_base + chip->ngpio; irq++) {
		irq_set_chip_data(irq, chip);
		irq_set_chip_and_handler(irq, &mtk_gpio_irqchip, handle_simple_irq);
		irq_set_nested_thread(irq, 1);
		irq_set_noprobe(irq);
	}

	return 0;
}

/******************************************************************************
* FUNCTION		: mtk_gpio_init()
* AUTHOR		: Wu Yin (wuyin@tp-link.net)
* DESCRIPTION	: mtk gpio init.
* INPUT			: N/A
*
* OUTPUT		: N/A
* RETURN		: N/A
* OTHERS		:
******************************************************************************/
int __init mtk_gpio_init(void)
{
	int err;

	err = gpiochip_add(&mtk_gpio_chip);
	if (err)
		panic("cannot add MTK GPIO chip, error=%d", err);

	mtk_gpio_irq_init(&mtk_gpio_chip);
	
	request_threaded_irq(SURFBOARDINT_GPIO, NULL, mtk_gpio_irq, IRQF_ONESHOT, "mtk-gpio", NULL);

	return 0;
}

arch_initcall(mtk_gpio_init);


int gpio_get_value(unsigned gpio)
{
	if (gpio < RALINK_GPIO_NUMBER) {
		return __mtk_gpio_get_value(gpio);
	}
	return __gpio_get_value(gpio);
}
EXPORT_SYMBOL(gpio_get_value);

void gpio_set_value(unsigned gpio, int value)
{
	if (gpio < RALINK_GPIO_NUMBER) {
		__mtk_gpio_set_value(gpio, value);
	}
	__gpio_set_value(gpio, value);
}
EXPORT_SYMBOL(gpio_set_value);

int gpio_to_irq(unsigned gpio)
{
	if (gpio > RALINK_GPIO_NUMBER) {
		return -EINVAL;
	}

	return MTK_GPIO_IRQ_BASE + gpio;
}
EXPORT_SYMBOL(gpio_to_irq);

int irq_to_gpio(unsigned irq)
{
	unsigned gpio = irq - MTK_GPIO_IRQ_BASE;

	if (gpio > RALINK_GPIO_NUMBER) {
		return -EINVAL;
	}

	return gpio;
}
EXPORT_SYMBOL(irq_to_gpio);

int mt7628_gpio_direction_output(unsigned gpio, int value)
{
	int ret = 0;
	if (gpio < RALINK_GPIO_NUMBER) {
		ret = mtk_gpio_direction_output(NULL, gpio, value);
	}
	
	return ret;
}
EXPORT_SYMBOL(mt7628_gpio_direction_output);

int mt7628_gpio_direction_input(unsigned gpio)
{
	int ret = 0;
	if (gpio < RALINK_GPIO_NUMBER) {
		ret = mtk_gpio_direction_input(NULL, gpio);
	}
	
	return ret;
}
EXPORT_SYMBOL(mt7628_gpio_direction_input);

int gpio_direction_select(unsigned gpio, int output)
{
	int ret = 0;
	
	ret = __mtk_gpio_direction_select(gpio, output);
	
	return ret;
}
EXPORT_SYMBOL(gpio_direction_select);