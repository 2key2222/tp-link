/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2013 Cavium, Inc.
 */
#ifndef _ASM_KVM_MIPS_VZ_H
#define _ASM_KVM_MIPS_VZ_H

struct kvm;

struct kvm_mips_vz {
	struct mutex guest_mm_lock;
	pgd_t *pgd;			/* Translations for this host. */
	spinlock_t irq_chip_lock;
	struct page *irq_chip;
	unsigned int asid[NR_CPUS];	/* Per CPU ASIDs for pgd. */
};

struct kvm_mips_vcpu_vz {
	struct kvm_vcpu *vcpu;
	u64 c0_entrylo0;
	u64 c0_entrylo1;
	u64 c0_context;
	u64 c0_userlocal;
	u64 c0_badvaddr;
	u64 c0_entryhi;
	u64 c0_epc;
	u64 c0_ebase;
	u64 c0_xcontext;
	u64 c0_errorepc;
	u64 c0_kscratch[6];
	u32 c0_pagemask;
	u32 c0_pagegrain;
	u32 c0_wired;
	u32 c0_hwrena;
	u32 c0_compare;
	u32 c0_status;
	u32 c0_cause;
	u32 c0_index;

	u32 c0_count; /* Not settable, value at last exit. */
	u32 c0_count_offset;

	int tlb_size;
	struct mipsvz_kvm_tlb_entry *tlb_state;

	u32 last_exit_insn;
	/* Saved  mips_kvm_rootsp[] value when we are off the CPU. */
	unsigned long rootsp;

	/* Protected by kvm_arch.irq_chip_lock, the value of Guestctl2[VIP] */
	u8 injected_ipx;

	struct hrtimer compare_timer;
	ktime_t compare_timer_read;

	bool have_counter_state;
};

bool mipsvz_page_fault(struct pt_regs *regs, unsigned long write,
		       unsigned long address);

bool mipsvz_cp_unusable(struct pt_regs *regs);
int mipsvz_arch_init(const void *opaque);
int mipsvz_arch_hardware_enable(void *garbage);
int mipsvz_init_vm(struct kvm *kvm, unsigned long type);

#endif /* _ASM_KVM_MIPS_VZ_H */
