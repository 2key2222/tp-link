/*
 * (C) Copyright 2000
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

/* #define	DEBUG	*/

#include <common.h>
#include <autoboot.h>
#include <cli.h>
#include <console.h>
#include <version.h>
#include <dm.h>
#include <asm/gpio.h>

DECLARE_GLOBAL_DATA_PTR;

extern int board_reset_gpio_get(void);
extern int board_sys_led(int onoff);

#if defined(CONFIG_HTTPD)
extern int NetLoopHttpd( void );
#endif

/*
 * Board-specific Platform code can reimplement show_boot_progress () if needed
 */
__weak void show_boot_progress(int val) {}

static void run_preboot_environment_command(void)
{
#ifdef CONFIG_PREBOOT
	char *p;

	p = getenv("preboot");
	if (p != NULL) {
# ifdef CONFIG_AUTOBOOT_KEYED
		int prev = disable_ctrlc(1);	/* disable Control C checking */
# endif

		run_command_list(p, -1, 0);

# ifdef CONFIG_AUTOBOOT_KEYED
		disable_ctrlc(prev);	/* restore Control C checking */
# endif
	}
#endif /* CONFIG_PREBOOT */
}

#if defined(CONFIG_HTTPD)
static int recovery_check(void)
{
    int reset_button = -1;

	printf("Checking for firmware recovery mode...\n");
	reset_button = board_reset_gpio_get();
	if (!reset_button)
	{
		printf("Reset button pushed ");
		int check_count = 6; /* 500ms * 6 = 3s */
		while(--check_count)
		{
			mdelay(500);
			reset_button = board_reset_gpio_get();
			if (!reset_button)
				continue;
			else
				break;
		}

		if (!check_count)
		{
			printf("more than 3 seconds, enter firmware recovery mode\n");
			return 1;
		}
		else
		{
			printf("less than 3 seconds, do nothing\n");
		}
	}
	else
	{
		printf("Reset button not pushed, do nothing\n");
	}

	return 0;
}
#endif

/* We come here after U-Boot is initialised and ready to process commands */
void main_loop(void)
{
	const char *s;

	bootstage_mark_name(BOOTSTAGE_ID_MAIN_LOOP, "main_loop");

#ifdef CONFIG_VERSION_VARIABLE
	setenv("ver", version_string);  /* set version variable */
#endif /* CONFIG_VERSION_VARIABLE */

	cli_init();

	run_preboot_environment_command();

#if defined(CONFIG_UPDATE_TFTP)
	update_tftp(0UL, NULL, NULL);
#endif /* CONFIG_UPDATE_TFTP */

	s = bootdelay_process();
	if (cli_process_fdt(&s))
		cli_secure_boot_cmd(s);

#if defined(CONFIG_HTTPD)
	/* check firmware recovery */
	if (recovery_check())
	{
		/* enter recovery mode */
		NetLoopHttpd();
	}
#endif /* CONFIG_HTTPD */

	autoboot_command(s);

	cli_loop();
	panic("No CLI available");
}
