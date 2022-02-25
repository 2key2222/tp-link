/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 1999 Ralf Baechle
 * Copyright (C) 1999 Silicon Graphics, Inc.
 */
#include <asm/mipsregs.h>
#include <asm/regdef.h>
#include <asm/stackframe.h>

	.macro tlb_do_page_fault, write
	NESTED(tlb_do_page_fault_\write, PT_SIZE, sp)
	SAVE_ALL
	MFC0	a2, CP0_BADVADDR
#ifdef CONFIG_KVM_MIPS_VZ
	mfc0	v0, CP0_BADINSTR
	mfc0	v1, CP0_BADINSTRP
	sw	v0, PT_BADINSTR(sp)
	sw	v1, PT_BADINSTRP(sp)
#endif
	KMODE
	move	a0, sp
	REG_S	a2, PT_BVADDR(sp)
	li	a1, \write
	PTR_LA	ra, ret_from_exception
	j	do_page_fault
	END(tlb_do_page_fault_\write)
	.endm

	tlb_do_page_fault 0
	tlb_do_page_fault 1
