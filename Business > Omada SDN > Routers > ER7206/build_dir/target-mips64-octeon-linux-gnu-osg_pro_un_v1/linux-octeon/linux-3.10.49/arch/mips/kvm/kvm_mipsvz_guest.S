/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2013 Cavium, Inc.
 */

#include <asm/stackframe.h>

#define START_GUEST_STACK_ADJUST (8 * 11)
	.set noreorder
	.p2align 5
LEAF(mipsvz_start_guest)
	daddiu	sp, sp, -START_GUEST_STACK_ADJUST
	sd	$16, (0 * 8)(sp)
	sd	$17, (1 * 8)(sp)
	sd	$18, (2 * 8)(sp)
	sd	$19, (3 * 8)(sp)
	sd	$20, (4 * 8)(sp)
	sd	$21, (5 * 8)(sp)
	sd	$22, (6 * 8)(sp)
	sd	$23, (7 * 8)(sp)
	/*	$24, t8 */
	/*	$25, t9 */
	/*	$26, K0 */
	/*	$27, K1 */
	sd	$28, (8 * 8)(sp) /* gp/current */
	/*	$29, sp */
	sd	$30, (9 * 8)(sp)
	sd	$31, (10 * 8)(sp)

	/* Save sp in the CPU specific slot */
	set_mips_kvm_rootsp sp, v0

	/*
	 * Move to EXL with interrupts enabled.  When we ERET to Guest
	 * mode, we can again process interrupts.
	 */
	mfc0	v0, CP0_STATUS
	ori	v0, ST0_EXL | ST0_IE
	mtc0	v0, CP0_STATUS

	dli	v0,1
	/* Set GuestMode (GM) bit */
	mfc0	v1, CP0_GUESTCTL0
	ins	v1, v0, MIPS_GUESTCTL0B_GM, 1
	mtc0	v1, CP0_GUESTCTL0

	/* Set the high order bit of CPU_ID_REG to indicate guest mode. */
	dmfc0	v1, CPU_ID_REG
	dins	v1, v0, 63, 1
	dmtc0	v1, CPU_ID_REG

	/* Load Guest register state */
	ld	v0, KVM_VCPU_ARCH_EPC(a0)
	ld	v1, KVM_VCPU_ARCH_HI(a0)
	ld	ta0, KVM_VCPU_ARCH_LO(a0)
	dmtc0	v0, CP0_EPC
	mthi	v1
	mtlo	ta0

	.set	push
	.set	noat
	ld	$1, KVM_VCPU_ARCH_R1(a0)
	ld	$2, KVM_VCPU_ARCH_R2(a0)
	ld	$3, KVM_VCPU_ARCH_R3(a0)
	ld	$5, KVM_VCPU_ARCH_R5(a0)
	ld	$6, KVM_VCPU_ARCH_R6(a0)
	ld	$7, KVM_VCPU_ARCH_R7(a0)
	ld	$8, KVM_VCPU_ARCH_R8(a0)
	ld	$9, KVM_VCPU_ARCH_R9(a0)
	ld	$10, KVM_VCPU_ARCH_R10(a0)
	ld	$11, KVM_VCPU_ARCH_R11(a0)
	ld	$12, KVM_VCPU_ARCH_R12(a0)
	ld	$13, KVM_VCPU_ARCH_R13(a0)
	ld	$14, KVM_VCPU_ARCH_R14(a0)
	ld	$15, KVM_VCPU_ARCH_R15(a0)
	ld	$16, KVM_VCPU_ARCH_R16(a0)
	ld	$17, KVM_VCPU_ARCH_R17(a0)
	ld	$18, KVM_VCPU_ARCH_R18(a0)
	ld	$19, KVM_VCPU_ARCH_R19(a0)
	ld	$20, KVM_VCPU_ARCH_R20(a0)
	ld	$21, KVM_VCPU_ARCH_R21(a0)
	ld	$22, KVM_VCPU_ARCH_R22(a0)
	ld	$23, KVM_VCPU_ARCH_R23(a0)
	ld	$24, KVM_VCPU_ARCH_R24(a0)
	ld	$25, KVM_VCPU_ARCH_R25(a0)
	ld	$26, KVM_VCPU_ARCH_R26(a0)
	ld	$27, KVM_VCPU_ARCH_R27(a0)
	ld	$28, KVM_VCPU_ARCH_R28(a0)
	ld	$29, KVM_VCPU_ARCH_R29(a0)
	ld	$30, KVM_VCPU_ARCH_R30(a0)
	ld	$31, KVM_VCPU_ARCH_R31(a0)
	ld	$4, KVM_VCPU_ARCH_R4(a0) /* $4 == a0, do it last. */
	eret
	.set	pop

	.p2align 7
.Lmipsvz_exit_guest:
FEXPORT(mipsvz_exit_guest)

	/* Clear sp in the CPU specific slot */
	CPU_ID_MFC0	k0, CPU_ID_REG
	get_mips_kvm_rootsp
	move	sp, k1
	set_mips_kvm_rootsp zero, v0

	ld	$16, (0 * 8)(sp)
	ld	$17, (1 * 8)(sp)
	ld	$18, (2 * 8)(sp)
	ld	$19, (3 * 8)(sp)
	ld	$20, (4 * 8)(sp)
	ld	$21, (5 * 8)(sp)
	ld	$22, (6 * 8)(sp)
	ld	$23, (7 * 8)(sp)
	/*	$24, t8 */
	/*	$25, t9 */
	/*	$26, K0 */
	/*	$27, K1 */
	ld	$28, (8 * 8)(sp) /* gp/current */
	/*	$29, sp */
	ld	$30, (9 * 8)(sp)
	ld	$31, (10 * 8)(sp)

	jr	ra
	 daddiu	sp, sp, START_GUEST_STACK_ADJUST
	END(mipsvz_start_guest)

	.p2align 5
	.set mips64r2

LEAF(mipsvz_install_fpu)
	ldc1	$f0, (KVM_VCPU_ARCH_FPR + (0 * 8))(a0)
	ldc1	$f1, (KVM_VCPU_ARCH_FPR + (1 * 8))(a0)
	ldc1	$f2, (KVM_VCPU_ARCH_FPR + (2 * 8))(a0)
	ldc1	$f3, (KVM_VCPU_ARCH_FPR + (3 * 8))(a0)
	ldc1	$f4, (KVM_VCPU_ARCH_FPR + (4 * 8))(a0)
	ldc1	$f5, (KVM_VCPU_ARCH_FPR + (5 * 8))(a0)
	ldc1	$f6, (KVM_VCPU_ARCH_FPR + (6 * 8))(a0)
	ldc1	$f7, (KVM_VCPU_ARCH_FPR + (7 * 8))(a0)
	ldc1	$f8, (KVM_VCPU_ARCH_FPR + (8 * 8))(a0)
	ldc1	$f9, (KVM_VCPU_ARCH_FPR + (9 * 8))(a0)
	ldc1	$f10, (KVM_VCPU_ARCH_FPR + (10 * 8))(a0)
	ldc1	$f11, (KVM_VCPU_ARCH_FPR + (11 * 8))(a0)
	ldc1	$f12, (KVM_VCPU_ARCH_FPR + (12 * 8))(a0)
	ldc1	$f13, (KVM_VCPU_ARCH_FPR + (13 * 8))(a0)
	ldc1	$f14, (KVM_VCPU_ARCH_FPR + (14 * 8))(a0)
	ldc1	$f15, (KVM_VCPU_ARCH_FPR + (15 * 8))(a0)
	ldc1	$f16, (KVM_VCPU_ARCH_FPR + (16 * 8))(a0)
	ldc1	$f17, (KVM_VCPU_ARCH_FPR + (17 * 8))(a0)
	ldc1	$f18, (KVM_VCPU_ARCH_FPR + (18 * 8))(a0)
	ldc1	$f19, (KVM_VCPU_ARCH_FPR + (19 * 8))(a0)
	ldc1	$f20, (KVM_VCPU_ARCH_FPR + (20 * 8))(a0)
	ldc1	$f21, (KVM_VCPU_ARCH_FPR + (21 * 8))(a0)
	ldc1	$f22, (KVM_VCPU_ARCH_FPR + (22 * 8))(a0)
	ldc1	$f23, (KVM_VCPU_ARCH_FPR + (23 * 8))(a0)
	ldc1	$f24, (KVM_VCPU_ARCH_FPR + (24 * 8))(a0)
	ldc1	$f25, (KVM_VCPU_ARCH_FPR + (25 * 8))(a0)
	ldc1	$f26, (KVM_VCPU_ARCH_FPR + (26 * 8))(a0)
	ldc1	$f27, (KVM_VCPU_ARCH_FPR + (27 * 8))(a0)
	ldc1	$f28, (KVM_VCPU_ARCH_FPR + (28 * 8))(a0)
	ldc1	$f29, (KVM_VCPU_ARCH_FPR + (29 * 8))(a0)
	ldc1	$f30, (KVM_VCPU_ARCH_FPR + (30 * 8))(a0)
	ldc1	$f31, (KVM_VCPU_ARCH_FPR + (31 * 8))(a0)

	lw	t0, KVM_VCPU_ARCH_FCSR(a0)
	ctc1	t0, $31

	lw	t0, KVM_VCPU_ARCH_FENR(a0)
	ctc1	t0, $28

	lw	t0, KVM_VCPU_ARCH_FEXR(a0)
	ctc1	t0, $26

	lw	t0, KVM_VCPU_ARCH_FCCR(a0)

	jr	ra
	 ctc1	t0, $25

	END(mipsvz_install_fpu)

LEAF(mipsvz_readout_fpu)
	sdc1	$f0, (KVM_VCPU_ARCH_FPR + (0 * 8))(a0)
	sdc1	$f1, (KVM_VCPU_ARCH_FPR + (1 * 8))(a0)
	sdc1	$f2, (KVM_VCPU_ARCH_FPR + (2 * 8))(a0)
	sdc1	$f3, (KVM_VCPU_ARCH_FPR + (3 * 8))(a0)
	sdc1	$f4, (KVM_VCPU_ARCH_FPR + (4 * 8))(a0)
	sdc1	$f5, (KVM_VCPU_ARCH_FPR + (5 * 8))(a0)
	sdc1	$f6, (KVM_VCPU_ARCH_FPR + (6 * 8))(a0)
	sdc1	$f7, (KVM_VCPU_ARCH_FPR + (7 * 8))(a0)
	sdc1	$f8, (KVM_VCPU_ARCH_FPR + (8 * 8))(a0)
	sdc1	$f9, (KVM_VCPU_ARCH_FPR + (9 * 8))(a0)
	sdc1	$f10, (KVM_VCPU_ARCH_FPR + (10 * 8))(a0)
	sdc1	$f11, (KVM_VCPU_ARCH_FPR + (11 * 8))(a0)
	sdc1	$f12, (KVM_VCPU_ARCH_FPR + (12 * 8))(a0)
	sdc1	$f13, (KVM_VCPU_ARCH_FPR + (13 * 8))(a0)
	sdc1	$f14, (KVM_VCPU_ARCH_FPR + (14 * 8))(a0)
	sdc1	$f15, (KVM_VCPU_ARCH_FPR + (15 * 8))(a0)
	sdc1	$f16, (KVM_VCPU_ARCH_FPR + (16 * 8))(a0)
	sdc1	$f17, (KVM_VCPU_ARCH_FPR + (17 * 8))(a0)
	sdc1	$f18, (KVM_VCPU_ARCH_FPR + (18 * 8))(a0)
	sdc1	$f19, (KVM_VCPU_ARCH_FPR + (19 * 8))(a0)
	sdc1	$f20, (KVM_VCPU_ARCH_FPR + (20 * 8))(a0)
	sdc1	$f21, (KVM_VCPU_ARCH_FPR + (21 * 8))(a0)
	sdc1	$f22, (KVM_VCPU_ARCH_FPR + (22 * 8))(a0)
	sdc1	$f23, (KVM_VCPU_ARCH_FPR + (23 * 8))(a0)
	sdc1	$f24, (KVM_VCPU_ARCH_FPR + (24 * 8))(a0)
	sdc1	$f25, (KVM_VCPU_ARCH_FPR + (25 * 8))(a0)
	sdc1	$f26, (KVM_VCPU_ARCH_FPR + (26 * 8))(a0)
	sdc1	$f27, (KVM_VCPU_ARCH_FPR + (27 * 8))(a0)
	sdc1	$f28, (KVM_VCPU_ARCH_FPR + (28 * 8))(a0)
	sdc1	$f29, (KVM_VCPU_ARCH_FPR + (29 * 8))(a0)
	sdc1	$f30, (KVM_VCPU_ARCH_FPR + (30 * 8))(a0)
	sdc1	$f31, (KVM_VCPU_ARCH_FPR + (31 * 8))(a0)

	cfc1	t0, $31
	sw	t0, KVM_VCPU_ARCH_FCSR(a0)

	cfc1	t0, $28
	sw	t0, KVM_VCPU_ARCH_FENR(a0)

	cfc1	t0, $26
	sw	t0, KVM_VCPU_ARCH_FEXR(a0)

	cfc1	t0, $25
	sw	t0, KVM_VCPU_ARCH_FCCR(a0)

	cfc1	t0, $0

	jr	ra
	 sw	t0, KVM_VCPU_ARCH_FIR(a0)

	END(mipsvz_readout_fpu)
