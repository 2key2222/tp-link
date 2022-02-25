/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2013 Cavium, Inc.
 */

#include <linux/kernel.h>
#include <linux/virtio_console.h>

#include <asm/mipsregs.h>

/*
 * Emit one character to the boot console.
 */
int prom_putchar(char c)
{
#if 0
	register char *pc asm("a1");

	pc = &c;
	asm volatile(
		"li	$v0, 0\n\t"	/* console output*/
		"li	$a0, 0\n\t"	/* console port 0*/
		"li	$a2, 1\n\t"	/* one char only */
		".word 0x42000028"	/* HYPCALL */
		: : "r" (pc), "m" (*pc) : "v0", "a0", "a2"
		);
#endif
	hypcall3(0 /* Console output */, 0 /*  port 0 */, (unsigned long)&c, 1 /* len == 1 */);

	return 1;
}

#ifdef CONFIG_VIRTIO_CONSOLE
static int paravirt_put_chars(u32 vtermno, const char *buf, int count)
{
	hypcall3(0 /* Console output */, vtermno, (unsigned long)buf, count);
	return count;
}

static int __init paravirt_cons_init(void)
{
	virtio_cons_early_init(paravirt_put_chars);
	return 0;
}
core_initcall(paravirt_cons_init);

#endif
