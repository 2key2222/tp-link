	.section .mdebug.abiN32
	.previous
	.gnu_attribute 4, 3
	.abicalls
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.section	.text.startup.main,"ax",@progbits
	.align	2
	.globl	main
.LFB195 = .
	.file 1 "lib/asm-offsets.c"
	.loc 1 20 0
	.cfi_startproc
	.set	nomips16
	.ent	main
	.type	main, @function
main:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.loc 1 22 0
#APP
 # 22 "lib/asm-offsets.c" 1
	
->GENERATED_GBL_DATA_SIZE 320 (sizeof(struct global_data) + 15) & ~15
 # 0 "" 2
	.loc 1 25 0
 # 25 "lib/asm-offsets.c" 1
	
->GENERATED_BD_INFO_SIZE 80 (sizeof(struct bd_info) + 15) & ~15
 # 0 "" 2
	.loc 1 28 0
 # 28 "lib/asm-offsets.c" 1
	
->GD_SIZE 320 sizeof(struct global_data)
 # 0 "" 2
	.loc 1 30 0
 # 30 "lib/asm-offsets.c" 1
	
->GD_BD 0 offsetof(struct global_data, bd)
 # 0 "" 2
	.loc 1 43 0
#NO_APP
	.set	noreorder
	.set	nomacro
	j	$31
	move	$2,$0
	.set	macro
	.set	reorder

	.end	main
	.cfi_endproc
.LFE195:
	.size	main, .-main
	.text
.Letext0:
	.file 2 "/home/ubuntu/tp-link/ER7206_trunk/tplink/u-boot/sdk-3.x/bootloader/u-boot_rtl8367x/include/asm/types.h"
	.file 3 "/home/ubuntu/tp-link/ER7206_trunk/tplink/u-boot/sdk-3.x/bootloader/u-boot_rtl8367x/include/linux/types.h"
	.file 4 "/home/ubuntu/tp-link/ER7206_trunk/tplink/u-boot/sdk-3.x/bootloader/u-boot_rtl8367x/include/asm/u-boot.h"
	.file 5 "/home/ubuntu/tp-link/ER7206_trunk/tplink/u-boot/sdk-3.x/bootloader/u-boot_rtl8367x/include/net.h"
	.file 6 "/home/ubuntu/tp-link/ER7206_trunk/tplink/u-boot/sdk-3.x/bootloader/u-boot_rtl8367x/include/asm/u-boot-mips.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0x3e5
	.2byte	0x2
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF68
	.byte	0x1
	.4byte	.LASF69
	.4byte	.LASF70
	.4byte	.Ldebug_ranges0+0
	.4byte	0
	.4byte	0
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.4byte	.LASF0
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF1
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.4byte	.LASF2
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.4byte	.LASF3
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.4byte	.LASF4
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.ascii	"int\000"
	.uleb128 0x4
	.4byte	.LASF7
	.byte	0x2
	.byte	0x1c
	.4byte	0x5e
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF5
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.4byte	.LASF6
	.uleb128 0x4
	.4byte	.LASF8
	.byte	0x2
	.byte	0x27
	.4byte	0x77
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.4byte	.LASF9
	.uleb128 0x5
	.ascii	"u64\000"
	.byte	0x2
	.byte	0x49
	.4byte	0x77
	.uleb128 0x4
	.4byte	.LASF10
	.byte	0x2
	.byte	0x53
	.4byte	0x7e
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF11
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.4byte	.LASF12
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.4byte	.LASF13
	.uleb128 0x4
	.4byte	.LASF14
	.byte	0x3
	.byte	0x5d
	.4byte	0x30
	.uleb128 0x4
	.4byte	.LASF15
	.byte	0x3
	.byte	0x6d
	.4byte	0x53
	.uleb128 0x4
	.4byte	.LASF16
	.byte	0x3
	.byte	0x70
	.4byte	0x6c
	.uleb128 0x6
	.byte	0x4
	.uleb128 0x7
	.4byte	.LASF32
	.byte	0x50
	.byte	0x4
	.byte	0x18
	.4byte	0x19d
	.uleb128 0x8
	.4byte	.LASF17
	.byte	0x4
	.byte	0x19
	.4byte	0x5e
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x8
	.4byte	.LASF18
	.byte	0x4
	.byte	0x1a
	.4byte	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0x8
	.4byte	.LASF19
	.byte	0x4
	.byte	0x1b
	.4byte	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0x8
	.4byte	.LASF20
	.byte	0x4
	.byte	0x1c
	.4byte	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0xc
	.uleb128 0x8
	.4byte	.LASF21
	.byte	0x4
	.byte	0x1d
	.4byte	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0x10
	.uleb128 0x8
	.4byte	.LASF22
	.byte	0x4
	.byte	0x1e
	.4byte	0x89
	.byte	0x2
	.byte	0x23
	.uleb128 0x18
	.uleb128 0x8
	.4byte	.LASF23
	.byte	0x4
	.byte	0x1f
	.4byte	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0x20
	.uleb128 0x8
	.4byte	.LASF24
	.byte	0x4
	.byte	0x20
	.4byte	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0x24
	.uleb128 0x8
	.4byte	.LASF25
	.byte	0x4
	.byte	0x21
	.4byte	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0x28
	.uleb128 0x8
	.4byte	.LASF26
	.byte	0x4
	.byte	0x23
	.4byte	0x19d
	.byte	0x2
	.byte	0x23
	.uleb128 0x2c
	.uleb128 0x8
	.4byte	.LASF27
	.byte	0x4
	.byte	0x24
	.4byte	0xbf
	.byte	0x2
	.byte	0x23
	.uleb128 0x38
	.uleb128 0x8
	.4byte	.LASF28
	.byte	0x4
	.byte	0x25
	.4byte	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0x40
	.uleb128 0x8
	.4byte	.LASF29
	.byte	0x4
	.byte	0x26
	.4byte	0xb4
	.byte	0x2
	.byte	0x23
	.uleb128 0x44
	.uleb128 0x8
	.4byte	.LASF30
	.byte	0x4
	.byte	0x27
	.4byte	0xa9
	.byte	0x2
	.byte	0x23
	.uleb128 0x48
	.byte	0
	.uleb128 0x9
	.4byte	0x29
	.4byte	0x1ad
	.uleb128 0xa
	.4byte	0x94
	.byte	0x5
	.byte	0
	.uleb128 0x4
	.4byte	.LASF31
	.byte	0x4
	.byte	0x29
	.4byte	0xcc
	.uleb128 0xb
	.byte	0x4
	.4byte	0x1ad
	.uleb128 0x7
	.4byte	.LASF33
	.byte	0x40
	.byte	0x5
	.byte	0x51
	.4byte	0x273
	.uleb128 0x8
	.4byte	.LASF34
	.byte	0x5
	.byte	0x52
	.4byte	0x273
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x8
	.4byte	.LASF35
	.byte	0x5
	.byte	0x53
	.4byte	0x19d
	.byte	0x2
	.byte	0x23
	.uleb128 0x10
	.uleb128 0x8
	.4byte	.LASF36
	.byte	0x5
	.byte	0x54
	.4byte	0x4c
	.byte	0x2
	.byte	0x23
	.uleb128 0x18
	.uleb128 0x8
	.4byte	.LASF37
	.byte	0x5
	.byte	0x55
	.4byte	0x4c
	.byte	0x2
	.byte	0x23
	.uleb128 0x1c
	.uleb128 0x8
	.4byte	.LASF38
	.byte	0x5
	.byte	0x57
	.4byte	0x29e
	.byte	0x2
	.byte	0x23
	.uleb128 0x20
	.uleb128 0x8
	.4byte	.LASF39
	.byte	0x5
	.byte	0x58
	.4byte	0x2be
	.byte	0x2
	.byte	0x23
	.uleb128 0x24
	.uleb128 0x8
	.4byte	.LASF40
	.byte	0x5
	.byte	0x59
	.4byte	0x2d4
	.byte	0x2
	.byte	0x23
	.uleb128 0x28
	.uleb128 0x8
	.4byte	.LASF41
	.byte	0x5
	.byte	0x5a
	.4byte	0x2e6
	.byte	0x2
	.byte	0x23
	.uleb128 0x2c
	.uleb128 0x8
	.4byte	.LASF42
	.byte	0x5
	.byte	0x5e
	.4byte	0x2d4
	.byte	0x2
	.byte	0x23
	.uleb128 0x30
	.uleb128 0x8
	.4byte	.LASF43
	.byte	0x5
	.byte	0x5f
	.4byte	0x298
	.byte	0x2
	.byte	0x23
	.uleb128 0x34
	.uleb128 0x8
	.4byte	.LASF44
	.byte	0x5
	.byte	0x60
	.4byte	0x4c
	.byte	0x2
	.byte	0x23
	.uleb128 0x38
	.uleb128 0x8
	.4byte	.LASF45
	.byte	0x5
	.byte	0x61
	.4byte	0xca
	.byte	0x2
	.byte	0x23
	.uleb128 0x3c
	.byte	0
	.uleb128 0x9
	.4byte	0xa2
	.4byte	0x283
	.uleb128 0xa
	.4byte	0x94
	.byte	0xf
	.byte	0
	.uleb128 0xc
	.byte	0x1
	.4byte	0x4c
	.4byte	0x298
	.uleb128 0xd
	.4byte	0x298
	.uleb128 0xd
	.4byte	0x1b8
	.byte	0
	.uleb128 0xb
	.byte	0x4
	.4byte	0x1be
	.uleb128 0xb
	.byte	0x4
	.4byte	0x283
	.uleb128 0xc
	.byte	0x1
	.4byte	0x4c
	.4byte	0x2be
	.uleb128 0xd
	.4byte	0x298
	.uleb128 0xd
	.4byte	0xca
	.uleb128 0xd
	.4byte	0x4c
	.byte	0
	.uleb128 0xb
	.byte	0x4
	.4byte	0x2a4
	.uleb128 0xc
	.byte	0x1
	.4byte	0x4c
	.4byte	0x2d4
	.uleb128 0xd
	.4byte	0x298
	.byte	0
	.uleb128 0xb
	.byte	0x4
	.4byte	0x2c4
	.uleb128 0xe
	.byte	0x1
	.4byte	0x2e6
	.uleb128 0xd
	.4byte	0x298
	.byte	0
	.uleb128 0xb
	.byte	0x4
	.4byte	0x2da
	.uleb128 0xf
	.4byte	.LASF56
	.byte	0x4
	.byte	0x5
	.2byte	0x1b8
	.4byte	0x34e
	.uleb128 0x10
	.4byte	.LASF46
	.sleb128 0
	.uleb128 0x10
	.4byte	.LASF47
	.sleb128 1
	.uleb128 0x11
	.ascii	"ARP\000"
	.sleb128 2
	.uleb128 0x10
	.4byte	.LASF48
	.sleb128 3
	.uleb128 0x10
	.4byte	.LASF49
	.sleb128 4
	.uleb128 0x10
	.4byte	.LASF50
	.sleb128 5
	.uleb128 0x11
	.ascii	"DNS\000"
	.sleb128 6
	.uleb128 0x11
	.ascii	"NFS\000"
	.sleb128 7
	.uleb128 0x11
	.ascii	"CDP\000"
	.sleb128 8
	.uleb128 0x10
	.4byte	.LASF51
	.sleb128 9
	.uleb128 0x10
	.4byte	.LASF52
	.sleb128 10
	.uleb128 0x10
	.4byte	.LASF53
	.sleb128 11
	.uleb128 0x10
	.4byte	.LASF54
	.sleb128 12
	.uleb128 0x10
	.4byte	.LASF55
	.sleb128 13
	.byte	0
	.uleb128 0xf
	.4byte	.LASF57
	.byte	0x4
	.byte	0x5
	.2byte	0x205
	.4byte	0x374
	.uleb128 0x10
	.4byte	.LASF58
	.sleb128 0
	.uleb128 0x10
	.4byte	.LASF59
	.sleb128 1
	.uleb128 0x10
	.4byte	.LASF60
	.sleb128 2
	.uleb128 0x10
	.4byte	.LASF61
	.sleb128 3
	.byte	0
	.uleb128 0x12
	.byte	0x1
	.4byte	.LASF71
	.byte	0x1
	.byte	0x13
	.byte	0x1
	.4byte	0x4c
	.4byte	.LFB195
	.4byte	.LFE195
	.byte	0x2
	.byte	0x8d
	.sleb128 0
	.byte	0x1
	.uleb128 0x9
	.4byte	0xa2
	.4byte	0x398
	.uleb128 0x13
	.byte	0
	.uleb128 0x14
	.4byte	.LASF62
	.byte	0x6
	.byte	0x9
	.4byte	0x38d
	.byte	0x1
	.byte	0x1
	.uleb128 0x14
	.4byte	.LASF63
	.byte	0x6
	.byte	0xf
	.4byte	0xa9
	.byte	0x1
	.byte	0x1
	.uleb128 0x14
	.4byte	.LASF64
	.byte	0x6
	.byte	0x15
	.4byte	0x38d
	.byte	0x1
	.byte	0x1
	.uleb128 0x14
	.4byte	.LASF65
	.byte	0x5
	.byte	0x6b
	.4byte	0x298
	.byte	0x1
	.byte	0x1
	.uleb128 0x15
	.4byte	.LASF66
	.byte	0x5
	.2byte	0x20b
	.4byte	0x34e
	.byte	0x1
	.byte	0x1
	.uleb128 0x15
	.4byte	.LASF67
	.byte	0x5
	.2byte	0x23d
	.4byte	0x2ec
	.byte	0x1
	.byte	0x1
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x55
	.uleb128 0x6
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x52
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x4
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.uleb128 0x2117
	.uleb128 0xc
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x21
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"",@progbits
	.4byte	0x1c
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	.LFB195
	.4byte	.LFE195-.LFB195
	.4byte	0
	.4byte	0
	.section	.debug_ranges,"",@progbits
.Ldebug_ranges0:
	.4byte	.LFB195
	.4byte	.LFE195
	.4byte	0
	.4byte	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF45:
	.ascii	"priv\000"
.LASF17:
	.ascii	"bi_baudrate\000"
.LASF39:
	.ascii	"send\000"
.LASF50:
	.ascii	"PING\000"
.LASF8:
	.ascii	"__u64\000"
.LASF29:
	.ascii	"bi_uboot_map_size\000"
.LASF37:
	.ascii	"state\000"
.LASF63:
	.ascii	"__bss_end\000"
.LASF66:
	.ascii	"net_state\000"
.LASF25:
	.ascii	"bi_flashoffset\000"
.LASF11:
	.ascii	"sizetype\000"
.LASF60:
	.ascii	"NETLOOP_SUCCESS\000"
.LASF70:
	.ascii	"/home/ubuntu/tp-link/ER7206_trunk/tplink/u-boot/sdk-3.x/"
	.ascii	"bootloader/u-boot_rtl8367x\000"
.LASF67:
	.ascii	"net_loop_last_protocol\000"
.LASF56:
	.ascii	"proto_t\000"
.LASF71:
	.ascii	"main\000"
.LASF49:
	.ascii	"DHCP\000"
.LASF51:
	.ascii	"NETCONS\000"
.LASF4:
	.ascii	"short int\000"
.LASF20:
	.ascii	"bi_boot_params\000"
.LASF30:
	.ascii	"bi_bootflags\000"
.LASF33:
	.ascii	"eth_device\000"
.LASF18:
	.ascii	"bi_ip_addr\000"
.LASF7:
	.ascii	"__u32\000"
.LASF46:
	.ascii	"BOOTP\000"
.LASF35:
	.ascii	"enetaddr\000"
.LASF69:
	.ascii	"lib/asm-offsets.c\000"
.LASF36:
	.ascii	"iobase\000"
.LASF22:
	.ascii	"bi_memsize\000"
.LASF31:
	.ascii	"bd_t\000"
.LASF6:
	.ascii	"long long int\000"
.LASF48:
	.ascii	"TFTPGET\000"
.LASF59:
	.ascii	"NETLOOP_RESTART\000"
.LASF12:
	.ascii	"long int\000"
.LASF24:
	.ascii	"bi_flashsize\000"
.LASF53:
	.ascii	"TFTPSRV\000"
.LASF65:
	.ascii	"eth_current\000"
.LASF34:
	.ascii	"name\000"
.LASF61:
	.ascii	"NETLOOP_FAIL\000"
.LASF32:
	.ascii	"bd_info\000"
.LASF62:
	.ascii	"__bss_start\000"
.LASF0:
	.ascii	"unsigned char\000"
.LASF14:
	.ascii	"ulong\000"
.LASF3:
	.ascii	"signed char\000"
.LASF16:
	.ascii	"uint64_t\000"
.LASF9:
	.ascii	"long long unsigned int\000"
.LASF15:
	.ascii	"uint32_t\000"
.LASF5:
	.ascii	"unsigned int\000"
.LASF58:
	.ascii	"NETLOOP_CONTINUE\000"
.LASF54:
	.ascii	"TFTPPUT\000"
.LASF47:
	.ascii	"RARP\000"
.LASF2:
	.ascii	"short unsigned int\000"
.LASF64:
	.ascii	"__image_copy_end\000"
.LASF13:
	.ascii	"char\000"
.LASF38:
	.ascii	"init\000"
.LASF42:
	.ascii	"write_hwaddr\000"
.LASF41:
	.ascii	"halt\000"
.LASF28:
	.ascii	"bi_uboot_ram_used_size\000"
.LASF1:
	.ascii	"long unsigned int\000"
.LASF55:
	.ascii	"LINKLOCAL\000"
.LASF68:
	.ascii	"GNU C 4.7.0\000"
.LASF10:
	.ascii	"phys_size_t\000"
.LASF21:
	.ascii	"bi_memstart\000"
.LASF26:
	.ascii	"bi_enetaddr\000"
.LASF52:
	.ascii	"SNTP\000"
.LASF27:
	.ascii	"bi_uboot_ram_addr\000"
.LASF23:
	.ascii	"bi_flashstart\000"
.LASF40:
	.ascii	"recv\000"
.LASF44:
	.ascii	"index\000"
.LASF19:
	.ascii	"bi_arch_number\000"
.LASF57:
	.ascii	"net_loop_state\000"
.LASF43:
	.ascii	"next\000"
	.ident	"GCC: (Cavium Inc. Version: SDK_3_1_0_p2 build 34) 4.7.0"
