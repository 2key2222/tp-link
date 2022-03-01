/*
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Marius Groeger <mgroeger@sysgo.de>
 *
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Alex Zuepke <azu@sysgo.de>
 *
 * (C) Copyright 2002
 * Gary Jennejohn, DENX Software Engineering, <garyj@denx.de>
 *
 * (C) Copyright 2004
 * DAVE Srl
 * http://www.dave-tech.it
 * http://www.wawnet.biz
 * mailto:info@wawnet.biz
 *
 * (C) Copyright 2004 Texas Insturments
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>

__weak void reset_misc(void)
{
}

#ifdef CONFIG_MVEBU_OC300
extern int gpio_lookup_name(const char *name, struct udevice **devp,
		     unsigned int *offsetp, unsigned int *gpiop);
extern int gpio_request(unsigned gpio, const char *label);
extern int gpio_direction_output(unsigned gpio, int value);
extern int gpio_free(unsigned gpio);
#endif

int do_reset(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
#ifdef CONFIG_MVEBU_OC300
    int ret = 0;
    unsigned int gpio = 0;
#endif

	puts ("resetting ...\n");

	udelay (50000);				/* wait 50 ms */

	disable_interrupts();

#ifdef CONFIG_MVEBU_OC300
    /* use watchdog(gpio55) to reset. */
    ret = gpio_lookup_name("C23", NULL, NULL, &gpio);
	if (ret) {
		printf("GPIO C23 not found\n");
		return 0;
	}

	ret = gpio_request(gpio, "init_sys_gpio");
	if (ret && ret != -EBUSY) {
		printf("GPIO: requesting pin %u failed\n", gpio);
		return -1;
	}

	gpio_direction_output(gpio, 0);

	if (ret != -EBUSY)
		gpio_free(gpio);

    while(1);
    return 0;
#else
	reset_misc();
	reset_cpu(0);

	/*NOTREACHED*/
	return 0;
#endif
}
