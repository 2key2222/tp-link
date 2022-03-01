/*
 * Copyright (C) 2016 Stefan Roese <sr@denx.de>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <dm.h>
#include <i2c.h>
#include <asm/io.h>
#include <asm/gpio.h>
#include <asm/arch/cpu.h>
#include <asm/arch/soc.h>
#ifdef CONFIG_BOARD_CONFIG_EEPROM
#include <mvebu_cfg_eeprom.h>
#endif

DECLARE_GLOBAL_DATA_PTR;

enum INIT_GPIO_TYPE {
	INIT_GPIO_SYS_LED = 0,
	INIT_GPIO_RESET,
	INIT_GPIO_WD_EN,
	INIT_GPIO_WD_FEED,
	INIT_GPIO_EMMC_RESET,
	INIT_GPIO_USB_PWR,
	INIT_GPIO_COUNT,
};

struct INIT_GPIO_OPS {
    char* gpio_name;
    int init_para;
	int (*init)(const char *gpio_name, int init_para);
};

static int board_init_led(const char *name, int delay);
static int board_gpio_out(const char *name, int onoff);

#ifdef CONFIG_MVEBU_ECK
static const struct INIT_GPIO_OPS init_gpio_ops[INIT_GPIO_COUNT] = {
    {"GPIO21",  500, board_init_led},    /* sys led */
    {"GPIO24",  1,   board_gpio_out},    /* reset */
    {"GPIO23",  1,   board_gpio_out},    /* watch dog enable */
    {"GPIO25",  1,   board_gpio_out}     /* watch dog feed */
    {"GPIO110", 1,   board_gpio_out},    /* emmc reset */
    {NULL, 0,   NULL},                   /* usb power */
};

#elif defined CONFIG_MVEBU_OC300
/* ap_mpp gpio pin named Axx for gpio0~gpio31
 * cp_mpp gpio pin named Bxx for gpio0~gpio31
 * cp_mpp gpio pin named Cxx for gpio32~gpio63
 */

static const struct INIT_GPIO_OPS init_gpio_ops[INIT_GPIO_COUNT] = {
    {"B30",  500, board_init_led},    /* sys led */
    {"B12",  1,   NULL},              /* reset */
    {"C22",  1,   board_gpio_out},    /* watch dog enable */
    {"C23",  1,   board_gpio_out},    /* watch dog feed */
    {NULL,   0, NULL},                /* emmc reset */
    {"C17",  1,   board_gpio_out}     /* usb power */
};

#else
static const INIT_GPIO_OPS init_gpio_ops[INIT_GPIO_COUNT] = {
    {NULL,   0, NULL},
    {NULL,   0, NULL},
    {NULL,   0, NULL},
    {NULL,   0, NULL},
    {NULL,   0, NULL},
    {NULL,   0, NULL}
};

#endif

static int board_gpio_out(const char *name, int onoff)
{
	int ret;
	unsigned int gpio;

	ret = gpio_lookup_name(name, NULL, NULL, &gpio);
	if (ret) {
		printf("GPIO: '%s' not found\n", name);
		return -1;
	}

	ret = gpio_request(gpio, "init_sys_gpio");
	if (ret && ret != -EBUSY) {
		printf("GPIO: requesting pin %u failed\n", gpio);
		return -1;
	}

	gpio_direction_output(gpio, onoff);

	if (ret != -EBUSY)
		gpio_free(gpio);

	return 0;
}

int __soc_early_init_f(void)
{
	return 0;
}

int soc_early_init_f(void)
			__attribute__((weak, alias("__soc_early_init_f")));

int board_early_init_f(void)
{
#ifdef CONFIG_MVEBU_SYS_INFO

	soc_early_init_f();

	/*
	 * Call this function to transfer data from address 0x4000000
	 * into a global struct, before code relocation.
	 */
	sys_info_init();
#endif
	return 0;
}

int board_sys_led(int onoff)
{
	return board_gpio_out(init_gpio_ops[INIT_GPIO_SYS_LED].gpio_name, onoff);
}

int board_reset_gpio_get(void)
{
	int ret;
	int value;
	unsigned int gpio;

	ret = gpio_lookup_name(init_gpio_ops[INIT_GPIO_RESET].gpio_name, NULL, NULL, &gpio);
	if (ret) {
		printf("GPIO: '%s' not found\n", init_gpio_ops[INIT_GPIO_RESET].gpio_name);
		return -1;
	}

	ret = gpio_request(gpio, "init_reset_gpio");
	if (ret && ret != -EBUSY) {
		printf("GPIO: requesting pin %u failed\n", gpio);
		return -1;
	}

	gpio_direction_input(gpio);
	value = gpio_get_value(gpio);

	if (ret != -EBUSY)
		gpio_free(gpio);

	return value;
}

int board_init(void)
{
	/* adress of boot parameters */
	gd->bd->bi_boot_params = CONFIG_SYS_SDRAM_BASE + 0x100;
#ifdef CONFIG_OF_CONTROL
	printf("U-Boot DT blob at : %p\n", gd->fdt_blob);
#endif

#ifdef CONFIG_BOARD_CONFIG_EEPROM
	cfg_eeprom_init();
#endif

	return 0;
}

static int board_init_led(const char *name, int delay)
{
	(void)board_gpio_out(name, 1);
	mdelay(delay);
	(void)board_gpio_out(name, 0);
    return 0;
}

int board_late_init(void)
{
	/* Pre-configure the USB ports (overcurrent, VBus) */

	return 0;
}

int last_stage_init(void)
{
    int i = 0; 

    for(i = 0; i < INIT_GPIO_COUNT;i ++)
    {
        if( (init_gpio_ops[i].gpio_name != NULL)
            &&(init_gpio_ops[i].init != NULL))
        {
            (void)init_gpio_ops[i].init(init_gpio_ops[i].gpio_name, init_gpio_ops[i].init_para);
        }
    }

	return 0;
}
