
u-boot-hi3518ev300.elf:     file format elf32-littlearm


Disassembly of section .text:

40700000 <__image_copy_start>:
40700000:	ea000515 	b	4070145c <reset>
40700004:	eafffffe 	b	40700004 <__image_copy_start+0x4>
40700008:	eafffffe 	b	40700008 <__image_copy_start+0x8>
4070000c:	eafffffe 	b	4070000c <__image_copy_start+0xc>
40700010:	eafffffe 	b	40700010 <__image_copy_start+0x10>
40700014:	eafffffe 	b	40700014 <__image_copy_start+0x14>
40700018:	eafffffe 	b	40700018 <__image_copy_start+0x18>
4070001c:	eafffffe 	b	4070001c <__image_copy_start+0x1c>
40700020:	deadbeef 	.word	0xdeadbeef
40700024:	deadbeef 	.word	0xdeadbeef
40700028:	deadbeef 	.word	0xdeadbeef
4070002c:	deadbeef 	.word	0xdeadbeef
40700030:	deadbeef 	.word	0xdeadbeef
40700034:	deadbeef 	.word	0xdeadbeef
40700038:	deadbeef 	.word	0xdeadbeef
4070003c:	deadbeef 	.word	0xdeadbeef

40700040 <__blank_zone_start>:
	...

40701440 <_blank_zone_start>:
40701440:	40700040 	.word	0x40700040

40701444 <_blank_zone_end>:
40701444:	40701440 	.word	0x40701440
40701448:	deadbeef 	.word	0xdeadbeef
4070144c:	deadbeef 	.word	0xdeadbeef

40701450 <_TEXT_BASE>:
40701450:	40700000 	.word	0x40700000

40701454 <_clr_remap_fmc_entry>:
40701454:	14001554 	.word	0x14001554

40701458 <_start_armboot>:
40701458:	40704520 	.word	0x40704520

4070145c <reset>:
4070145c:	ea000087 	b	40701680 <save_boot_params>

40701460 <save_boot_params_ret>:
40701460:	e10f0000 	mrs	r0, CPSR
40701464:	e200101f 	and	r1, r0, #31
40701468:	e331001a 	teq	r1, #26
4070146c:	13c0001f 	bicne	r0, r0, #31
40701470:	13800013 	orrne	r0, r0, #19
40701474:	e38000c0 	orr	r0, r0, #192	; 0xc0
40701478:	e129f000 	msr	CPSR_fc, r0
4070147c:	ee110f10 	mrc	15, 0, r0, cr1, cr0, {0}
40701480:	e3c00a02 	bic	r0, r0, #8192	; 0x2000
40701484:	ee010f10 	mcr	15, 0, r0, cr1, cr0, {0}
40701488:	e24f0090 	sub	r0, pc, #144	; 0x90
4070148c:	e2400c14 	sub	r0, r0, #20, 24	; 0x1400
40701490:	ee0c0f10 	mcr	15, 0, r0, cr12, cr0, {0}
40701494:	e59f023c 	ldr	r0, [pc, #572]	; 407016d8 <cpu_init_cp15+0x54>
40701498:	e5901140 	ldr	r1, [r0, #320]	; 0x140
4070149c:	e59f2238 	ldr	r2, [pc, #568]	; 407016dc <cpu_init_cp15+0x58>
407014a0:	e1510002 	cmp	r1, r2
407014a4:	1a000019 	bne	40701510 <normal_start_flow>
407014a8:	e1a0100d 	mov	r1, sp
407014ac:	e5801140 	str	r1, [r0, #320]	; 0x140
407014b0:	e51f0078 	ldr	r0, [pc, #-120]	; 40701440 <_blank_zone_start>
407014b4:	e51f106c 	ldr	r1, [pc, #-108]	; 40701450 <_TEXT_BASE>
407014b8:	e0400001 	sub	r0, r0, r1
407014bc:	e59f121c 	ldr	r1, [pc, #540]	; 407016e0 <cpu_init_cp15+0x5c>
407014c0:	e59fd21c 	ldr	sp, [pc, #540]	; 407016e4 <cpu_init_cp15+0x60>
407014c4:	e0800001 	add	r0, r0, r1
407014c8:	e3a01000 	mov	r1, #0
407014cc:	eb0000ad 	bl	40701788 <init_registers>
407014d0:	e59f0200 	ldr	r0, [pc, #512]	; 407016d8 <cpu_init_cp15+0x54>
407014d4:	eb00017e 	bl	40701ad4 <start_ddr_training>
407014d8:	e59f01f8 	ldr	r0, [pc, #504]	; 407016d8 <cpu_init_cp15+0x54>
407014dc:	e5901140 	ldr	r1, [r0, #320]	; 0x140
407014e0:	e1a0d001 	mov	sp, r1
407014e4:	e5901144 	ldr	r1, [r0, #324]	; 0x144
407014e8:	e1a0f001 	mov	pc, r1
407014ec:	e320f000 	nop	{0}
407014f0:	e320f000 	nop	{0}
407014f4:	e320f000 	nop	{0}
407014f8:	e320f000 	nop	{0}
407014fc:	e320f000 	nop	{0}
40701500:	e320f000 	nop	{0}
40701504:	e320f000 	nop	{0}
40701508:	e320f000 	nop	{0}
4070150c:	eafffffe 	b	4070150c <save_boot_params_ret+0xac>

40701510 <normal_start_flow>:
40701510:	e59fd1cc 	ldr	sp, [pc, #460]	; 407016e4 <cpu_init_cp15+0x60>
40701514:	eb000ab3 	bl	40703fe8 <uart_early_init>
40701518:	eb00004a 	bl	40701648 <msg_main_cpu_startup>
4070151c:	e59f01c4 	ldr	r0, [pc, #452]	; 407016e8 <cpu_init_cp15+0x64>
40701520:	e59f31c4 	ldr	r3, [pc, #452]	; 407016ec <cpu_init_cp15+0x68>
40701524:	e5803020 	str	r3, [r0, #32]
40701528:	e3a03001 	mov	r3, #1
4070152c:	e5803000 	str	r3, [r0]
40701530:	e1a00c2f 	lsr	r0, pc, #24
40701534:	e3500000 	cmp	r0, #0
40701538:	1a000005 	bne	40701554 <do_clr_remap>

4070153c <check_boot_type>:
4070153c:	e59f0194 	ldr	r0, [pc, #404]	; 407016d8 <cpu_init_cp15+0x54>
40701540:	e590008c 	ldr	r0, [r0, #140]	; 0x8c
40701544:	e1a06220 	lsr	r6, r0, #4
40701548:	e2066001 	and	r6, r6, #1
4070154c:	e3560001 	cmp	r6, #1
40701550:	351ff104 	ldrcc	pc, [pc, #-260]	; 40701454 <_clr_remap_fmc_entry>

40701554 <do_clr_remap>:
40701554:	e59f417c 	ldr	r4, [pc, #380]	; 407016d8 <cpu_init_cp15+0x54>
40701558:	e5940000 	ldr	r0, [r4]
4070155c:	e3800c01 	orr	r0, r0, #256	; 0x100
40701560:	e5840000 	str	r0, [r4]
40701564:	ee110f10 	mrc	15, 0, r0, cr1, cr0, {0}
40701568:	e3800a01 	orr	r0, r0, #4096	; 0x1000
4070156c:	ee010f10 	mcr	15, 0, r0, cr1, cr0, {0}
40701570:	e1a00e2f 	lsr	r0, pc, #28
40701574:	e3500004 	cmp	r0, #4
40701578:	3a000002 	bcc	40701588 <ddr_init>

4070157c <no_ddr_init>:
4070157c:	e24f0084 	sub	r0, pc, #132	; 0x84
40701580:	e2400c15 	sub	r0, r0, #5376	; 0x1500
40701584:	ea000017 	b	407015e8 <copy_to_ddr>

40701588 <ddr_init>:
40701588:	e51f0150 	ldr	r0, [pc, #-336]	; 40701440 <_blank_zone_start>
4070158c:	e51f1144 	ldr	r1, [pc, #-324]	; 40701450 <_TEXT_BASE>
40701590:	e0400001 	sub	r0, r0, r1
40701594:	e24f109c 	sub	r1, pc, #156	; 0x9c
40701598:	e2411c15 	sub	r1, r1, #5376	; 0x1500
4070159c:	e0800001 	add	r0, r0, r1
407015a0:	e3a01000 	mov	r1, #0
407015a4:	eb000077 	bl	40701788 <init_registers>
407015a8:	e59fd134 	ldr	sp, [pc, #308]	; 407016e4 <cpu_init_cp15+0x60>
407015ac:	e59f0124 	ldr	r0, [pc, #292]	; 407016d8 <cpu_init_cp15+0x54>
407015b0:	eb000147 	bl	40701ad4 <start_ddr_training>

407015b4 <check_boot_mode>:
407015b4:	e59f011c 	ldr	r0, [pc, #284]	; 407016d8 <cpu_init_cp15+0x54>
407015b8:	e590008c 	ldr	r0, [r0, #140]	; 0x8c
407015bc:	e1a06220 	lsr	r6, r0, #4
407015c0:	e2066001 	and	r6, r6, #1
407015c4:	e3560001 	cmp	r6, #1
407015c8:	1a000005 	bne	407015e4 <copy_flash_to_ddr>

407015cc <emmc_boot>:
407015cc:	e51f0184 	ldr	r0, [pc, #-388]	; 40701450 <_TEXT_BASE>
407015d0:	e59f1118 	ldr	r1, [pc, #280]	; 407016f0 <cpu_init_cp15+0x6c>
407015d4:	e59f2118 	ldr	r2, [pc, #280]	; 407016f4 <cpu_init_cp15+0x70>
407015d8:	e0421001 	sub	r1, r2, r1
407015dc:	eb000afb 	bl	407041d0 <emmc_boot_read>
407015e0:	ea000007 	b	40701604 <relocate>

407015e4 <copy_flash_to_ddr>:
407015e4:	e3a00305 	mov	r0, #335544320	; 0x14000000

407015e8 <copy_to_ddr>:
407015e8:	e59f1100 	ldr	r1, [pc, #256]	; 407016f0 <cpu_init_cp15+0x6c>
407015ec:	e1500001 	cmp	r0, r1
407015f0:	0a000bca 	beq	40704520 <start_armboot>
407015f4:	e59f20f4 	ldr	r2, [pc, #244]	; 407016f0 <cpu_init_cp15+0x6c>
407015f8:	e59f30f4 	ldr	r3, [pc, #244]	; 407016f4 <cpu_init_cp15+0x70>
407015fc:	e0432002 	sub	r2, r3, r2
40701600:	eb00000a 	bl	40701630 <memcpy>

40701604 <relocate>:
40701604:	e59f00ec 	ldr	r0, [pc, #236]	; 407016f8 <cpu_init_cp15+0x74>
40701608:	e590f000 	ldr	pc, [r0]

4070160c <bug>:
4070160c:	e320f000 	nop	{0}
40701610:	e320f000 	nop	{0}
40701614:	e320f000 	nop	{0}
40701618:	e320f000 	nop	{0}
4070161c:	e320f000 	nop	{0}
40701620:	e320f000 	nop	{0}
40701624:	e320f000 	nop	{0}
40701628:	e320f000 	nop	{0}
4070162c:	eafffffe 	b	4070162c <bug+0x20>

40701630 <memcpy>:
40701630:	e0802002 	add	r2, r0, r2

40701634 <memcpy_loop>:
40701634:	e8b007f8 	ldm	r0!, {r3, r4, r5, r6, r7, r8, r9, sl}
40701638:	e8a107f8 	stmia	r1!, {r3, r4, r5, r6, r7, r8, r9, sl}
4070163c:	e1500002 	cmp	r0, r2
40701640:	dafffffb 	ble	40701634 <memcpy_loop>
40701644:	e1a0f00e 	mov	pc, lr

40701648 <msg_main_cpu_startup>:
40701648:	e1a0500e 	mov	r5, lr
4070164c:	e28f0004 	add	r0, pc, #4
40701650:	eb000a71 	bl	4070401c <uart_early_puts>
40701654:	e1a0f005 	mov	pc, r5

40701658 <L10>:
40701658:	0a0d0a0d 	.word	0x0a0d0a0d
4070165c:	74737953 	.word	0x74737953
40701660:	73206d65 	.word	0x73206d65
40701664:	74726174 	.word	0x74726174
40701668:	0a0d7075 	.word	0x0a0d7075
4070166c:	00          	.byte	0x00
4070166d:	00          	.byte	0x00
	...

40701670 <c_runtime_cpu_setup>:
40701670:	ee070f15 	mcr	15, 0, r0, cr7, cr5, {0}
40701674:	ee070f9a 	mcr	15, 0, r0, cr7, cr10, {4}
40701678:	ee070f95 	mcr	15, 0, r0, cr7, cr5, {4}
4070167c:	e12fff1e 	bx	lr

40701680 <save_boot_params>:
40701680:	eaffff76 	b	40701460 <save_boot_params_ret>

40701684 <cpu_init_cp15>:
40701684:	e3a00000 	mov	r0, #0
40701688:	ee080f17 	mcr	15, 0, r0, cr8, cr7, {0}
4070168c:	ee070f15 	mcr	15, 0, r0, cr7, cr5, {0}
40701690:	ee070fd5 	mcr	15, 0, r0, cr7, cr5, {6}
40701694:	ee070f9a 	mcr	15, 0, r0, cr7, cr10, {4}
40701698:	ee070f95 	mcr	15, 0, r0, cr7, cr5, {4}
4070169c:	ee110f10 	mrc	15, 0, r0, cr1, cr0, {0}
407016a0:	e3c00a02 	bic	r0, r0, #8192	; 0x2000
407016a4:	e3c00007 	bic	r0, r0, #7
407016a8:	e3800002 	orr	r0, r0, #2
407016ac:	e3800b02 	orr	r0, r0, #2048	; 0x800
407016b0:	e3800a01 	orr	r0, r0, #4096	; 0x1000
407016b4:	ee010f10 	mcr	15, 0, r0, cr1, cr0, {0}
407016b8:	e1a0500e 	mov	r5, lr
407016bc:	ee101f10 	mrc	15, 0, r1, cr0, cr0, {0}
407016c0:	e1a03a21 	lsr	r3, r1, #20
407016c4:	e203300f 	and	r3, r3, #15
407016c8:	e201400f 	and	r4, r1, #15
407016cc:	e1a02203 	lsl	r2, r3, #4
407016d0:	e1842002 	orr	r2, r4, r2
407016d4:	e1a0f005 	mov	pc, r5
407016d8:	12020000 	.word	0x12020000
407016dc:	7a696a75 	.word	0x7a696a75
407016e0:	04010500 	.word	0x04010500
407016e4:	0401a000 	.word	0x0401a000
407016e8:	12050000 	.word	0x12050000
407016ec:	02faf080 	.word	0x02faf080
407016f0:	40700000 	.word	0x40700000
407016f4:	4073b18c 	.word	0x4073b18c
407016f8:	40701458 	.word	0x40701458

407016fc <reg_read>:
407016fc:	e590300c 	ldr	r3, [r0, #12]
40701700:	e5902000 	ldr	r2, [r0]
40701704:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
40701708:	e1a0eda3 	lsr	lr, r3, #27
4070170c:	e7e439d3 	ubfx	r3, r3, #19, #5
40701710:	e5922000 	ldr	r2, [r2]
40701714:	e2833001 	add	r3, r3, #1
40701718:	e3530020 	cmp	r3, #32
4070171c:	13e0c000 	mvnne	ip, #0
40701720:	11e0331c 	mvnne	r3, ip, lsl r3
40701724:	10032e32 	andne	r2, r3, r2, lsr lr
40701728:	e5903004 	ldr	r3, [r0, #4]
4070172c:	e0533002 	subs	r3, r3, r2
40701730:	13a03001 	movne	r3, #1
40701734:	e5813000 	str	r3, [r1]
40701738:	e49df004 	pop	{pc}		; (ldr pc, [sp], #4)

4070173c <reg_write>:
4070173c:	e92d4010 	push	{r4, lr}
40701740:	e590200c 	ldr	r2, [r0, #12]
40701744:	e5904000 	ldr	r4, [r0]
40701748:	e7e411d2 	ubfx	r1, r2, #3, #5
4070174c:	e5903004 	ldr	r3, [r0, #4]
40701750:	e2811001 	add	r1, r1, #1
40701754:	e590c008 	ldr	ip, [r0, #8]
40701758:	e3510020 	cmp	r1, #32
4070175c:	e594e000 	ldr	lr, [r4]
40701760:	17e425d2 	ubfxne	r2, r2, #11, #5
40701764:	13e00000 	mvnne	r0, #0
40701768:	11e01110 	mvnne	r1, r0, lsl r1
4070176c:	11ce1211 	bicne	r1, lr, r1, lsl r2
40701770:	11813213 	orrne	r3, r1, r3, lsl r2
40701774:	e5843000 	str	r3, [r4]
40701778:	e320f000 	nop	{0}
4070177c:	e25cc001 	subs	ip, ip, #1
40701780:	2afffffc 	bcs	40701778 <reg_write+0x3c>
40701784:	e8bd8010 	pop	{r4, pc}

40701788 <init_registers>:
40701788:	e92d40f7 	push	{r0, r1, r2, r4, r5, r6, r7, lr}
4070178c:	e1a06001 	mov	r6, r1
40701790:	e1a04000 	mov	r4, r0
40701794:	e3a07000 	mov	r7, #0
40701798:	e5943000 	ldr	r3, [r4]
4070179c:	e3530000 	cmp	r3, #0
407017a0:	1a000008 	bne	407017c8 <init_registers+0x40>
407017a4:	e5943004 	ldr	r3, [r4, #4]
407017a8:	e3530000 	cmp	r3, #0
407017ac:	1a000005 	bne	407017c8 <init_registers+0x40>
407017b0:	e5943008 	ldr	r3, [r4, #8]
407017b4:	e3530000 	cmp	r3, #0
407017b8:	1a000002 	bne	407017c8 <init_registers+0x40>
407017bc:	e594300c 	ldr	r3, [r4, #12]
407017c0:	e3530000 	cmp	r3, #0
407017c4:	0a00002e 	beq	40701884 <init_registers+0xfc>
407017c8:	e3560000 	cmp	r6, #0
407017cc:	e58d7004 	str	r7, [sp, #4]
407017d0:	e5945008 	ldr	r5, [r4, #8]
407017d4:	e594300c 	ldr	r3, [r4, #12]
407017d8:	0a000016 	beq	40701838 <init_registers+0xb0>
407017dc:	e3130002 	tst	r3, #2
407017e0:	0a000002 	beq	407017f0 <init_registers+0x68>
407017e4:	e1a00004 	mov	r0, r4
407017e8:	ebffffd3 	bl	4070173c <reg_write>
407017ec:	ea00000b 	b	40701820 <init_registers+0x98>
407017f0:	e3130802 	tst	r3, #131072	; 0x20000
407017f4:	0a00000b 	beq	40701828 <init_registers+0xa0>
407017f8:	e28d1004 	add	r1, sp, #4
407017fc:	e1a00004 	mov	r0, r4
40701800:	ebffffbd 	bl	407016fc <reg_read>
40701804:	e320f000 	nop	{0}
40701808:	e59d3004 	ldr	r3, [sp, #4]
4070180c:	e3530000 	cmp	r3, #0
40701810:	1afffff8 	bne	407017f8 <init_registers+0x70>
40701814:	e320f000 	nop	{0}
40701818:	e2555001 	subs	r5, r5, #1
4070181c:	2afffffc 	bcs	40701814 <init_registers+0x8c>
40701820:	e2844010 	add	r4, r4, #16
40701824:	eaffffdb 	b	40701798 <init_registers+0x10>
40701828:	e320f000 	nop	{0}
4070182c:	e2555001 	subs	r5, r5, #1
40701830:	2afffffc 	bcs	40701828 <init_registers+0xa0>
40701834:	eafffff9 	b	40701820 <init_registers+0x98>
40701838:	e3130004 	tst	r3, #4
4070183c:	1affffe8 	bne	407017e4 <init_registers+0x5c>
40701840:	e3130701 	tst	r3, #262144	; 0x40000
40701844:	0a00000a 	beq	40701874 <init_registers+0xec>
40701848:	e28d1004 	add	r1, sp, #4
4070184c:	e1a00004 	mov	r0, r4
40701850:	ebffffa9 	bl	407016fc <reg_read>
40701854:	e320f000 	nop	{0}
40701858:	e59d3004 	ldr	r3, [sp, #4]
4070185c:	e3530000 	cmp	r3, #0
40701860:	1afffff8 	bne	40701848 <init_registers+0xc0>
40701864:	e320f000 	nop	{0}
40701868:	e2555001 	subs	r5, r5, #1
4070186c:	2afffffc 	bcs	40701864 <init_registers+0xdc>
40701870:	eaffffea 	b	40701820 <init_registers+0x98>
40701874:	e320f000 	nop	{0}
40701878:	e2555001 	subs	r5, r5, #1
4070187c:	2afffffc 	bcs	40701874 <init_registers+0xec>
40701880:	eaffffe6 	b	40701820 <init_registers+0x98>
40701884:	e320f000 	nop	{0}
40701888:	e28dd00c 	add	sp, sp, #12
4070188c:	e8bd80f0 	pop	{r4, r5, r6, r7, pc}

40701890 <trng_init>:
40701890:	e59f2018 	ldr	r2, [pc, #24]	; 407018b0 <trng_init+0x20>
40701894:	e59231a0 	ldr	r3, [r2, #416]	; 0x1a0
40701898:	e3833008 	orr	r3, r3, #8
4070189c:	e58231a0 	str	r3, [r2, #416]	; 0x1a0
407018a0:	e59f300c 	ldr	r3, [pc, #12]	; 407018b4 <trng_init+0x24>
407018a4:	e3a0200a 	mov	r2, #10
407018a8:	e5832200 	str	r2, [r3, #512]	; 0x200
407018ac:	e12fff1e 	bx	lr
407018b0:	12010000 	.word	0x12010000
407018b4:	10090000 	.word	0x10090000

407018b8 <trng_deinit>:
407018b8:	e59f200c 	ldr	r2, [pc, #12]	; 407018cc <trng_deinit+0x14>
407018bc:	e59231a0 	ldr	r3, [r2, #416]	; 0x1a0
407018c0:	e3c33008 	bic	r3, r3, #8
407018c4:	e58231a0 	str	r3, [r2, #416]	; 0x1a0
407018c8:	e12fff1e 	bx	lr
407018cc:	12010000 	.word	0x12010000

407018d0 <start_svb>:
407018d0:	e59f21e8 	ldr	r2, [pc, #488]	; 40701ac0 <start_svb+0x1f0>
407018d4:	e92d4030 	push	{r4, r5, lr}
407018d8:	e24dd014 	sub	sp, sp, #20
407018dc:	e5923168 	ldr	r3, [r2, #360]	; 0x168
407018e0:	e3c338ff 	bic	r3, r3, #16711680	; 0xff0000
407018e4:	e3833601 	orr	r3, r3, #1048576	; 0x100000
407018e8:	e5823168 	str	r3, [r2, #360]	; 0x168
407018ec:	e59f31d0 	ldr	r3, [pc, #464]	; 40701ac4 <start_svb+0x1f4>
407018f0:	e59310bc 	ldr	r1, [r3, #188]	; 0xbc
407018f4:	e7e93051 	ubfx	r3, r1, #0, #10
407018f8:	e3530075 	cmp	r3, #117	; 0x75
407018fc:	93e01027 	mvnls	r1, #39	; 0x27
40701900:	9a000007 	bls	40701924 <start_svb+0x54>
40701904:	e3530fd2 	cmp	r3, #840	; 0x348
40701908:	93a010d4 	movls	r1, #212	; 0xd4
4070190c:	83a0106e 	movhi	r1, #110	; 0x6e
40701910:	90010391 	mulls	r1, r1, r3
40701914:	92411a06 	subls	r1, r1, #24576	; 0x6000
40701918:	924110e4 	subls	r1, r1, #228	; 0xe4
4070191c:	91a01521 	lsrls	r1, r1, #10
40701920:	92411028 	subls	r1, r1, #40	; 0x28
40701924:	e59f4198 	ldr	r4, [pc, #408]	; 40701ac4 <start_svb+0x1f4>
40701928:	e3a0e004 	mov	lr, #4
4070192c:	e3a03000 	mov	r3, #0
40701930:	e58d3000 	str	r3, [sp]
40701934:	e58d3004 	str	r3, [sp, #4]
40701938:	e58d3008 	str	r3, [sp, #8]
4070193c:	e58d300c 	str	r3, [sp, #12]
40701940:	e59430d8 	ldr	r3, [r4, #216]	; 0xd8
40701944:	e25ee001 	subs	lr, lr, #1
40701948:	e59d2004 	ldr	r2, [sp, #4]
4070194c:	e7e90853 	ubfx	r0, r3, #16, #10
40701950:	e7e93053 	ubfx	r3, r3, #0, #10
40701954:	e0802002 	add	r2, r0, r2
40701958:	e59d0000 	ldr	r0, [sp]
4070195c:	e58d2004 	str	r2, [sp, #4]
40701960:	e0833000 	add	r3, r3, r0
40701964:	e58d3000 	str	r3, [sp]
40701968:	e59400dc 	ldr	r0, [r4, #220]	; 0xdc
4070196c:	e59d500c 	ldr	r5, [sp, #12]
40701970:	e7e9c850 	ubfx	ip, r0, #16, #10
40701974:	e7e90050 	ubfx	r0, r0, #0, #10
40701978:	e08cc005 	add	ip, ip, r5
4070197c:	e59d5008 	ldr	r5, [sp, #8]
40701980:	e58dc00c 	str	ip, [sp, #12]
40701984:	e0800005 	add	r0, r0, r5
40701988:	e58d0008 	str	r0, [sp, #8]
4070198c:	1affffeb 	bne	40701940 <start_svb+0x70>
40701990:	e1a02122 	lsr	r2, r2, #2
40701994:	e0823123 	add	r3, r2, r3, lsr #2
40701998:	e300211a 	movw	r2, #282	; 0x11a
4070199c:	e0833120 	add	r3, r3, r0, lsr #2
407019a0:	e083312c 	add	r3, r3, ip, lsr #2
407019a4:	e1a03123 	lsr	r3, r3, #2
407019a8:	e1530002 	cmp	r3, r2
407019ac:	9a000037 	bls	40701a90 <start_svb+0x1c0>
407019b0:	e3510045 	cmp	r1, #69	; 0x45
407019b4:	9a000005 	bls	407019d0 <start_svb+0x100>
407019b8:	e3a020cd 	mov	r2, #205	; 0xcd
407019bc:	e0010192 	mul	r1, r2, r1
407019c0:	e2411b0e 	sub	r1, r1, #14336	; 0x3800
407019c4:	e241100e 	sub	r1, r1, #14
407019c8:	e0833521 	add	r3, r3, r1, lsr #10
407019cc:	e2833004 	add	r3, r3, #4
407019d0:	e59f10e8 	ldr	r1, [pc, #232]	; 40701ac0 <start_svb+0x1f0>
407019d4:	e3530095 	cmp	r3, #149	; 0x95
407019d8:	93a03096 	movls	r3, #150	; 0x96
407019dc:	e591215c 	ldr	r2, [r1, #348]	; 0x15c
407019e0:	e7d8281f 	bfc	r2, #16, #9
407019e4:	93822301 	orrls	r2, r2, #67108864	; 0x4000000
407019e8:	9a000004 	bls	40701a00 <start_svb+0x130>
407019ec:	e300015e 	movw	r0, #350	; 0x15e
407019f0:	e1530000 	cmp	r3, r0
407019f4:	97da2d1f 	bfcls	r2, #26, #1
407019f8:	83822301 	orrhi	r2, r2, #67108864	; 0x4000000
407019fc:	81a03000 	movhi	r3, r0
40701a00:	e7d82813 	bfi	r2, r3, #16, #9
40701a04:	e581215c 	str	r2, [r1, #348]	; 0x15c
40701a08:	e591209c 	ldr	r2, [r1, #156]	; 0x9c
40701a0c:	e35300be 	cmp	r3, #190	; 0xbe
40701a10:	e59f10b0 	ldr	r1, [pc, #176]	; 40701ac8 <start_svb+0x1f8>
40701a14:	e202200f 	and	r2, r2, #15
40701a18:	930033c6 	movwls	r3, #966	; 0x3c6
40701a1c:	e591002c 	ldr	r0, [r1, #44]	; 0x2c
40701a20:	9a000006 	bls	40701a40 <start_svb+0x170>
40701a24:	e3001135 	movw	r1, #309	; 0x135
40701a28:	e1530001 	cmp	r3, r1
40701a2c:	930015a5 	movwls	r1, #1445	; 0x5a5
40701a30:	83a03fc7 	movhi	r3, #796	; 0x31c
40701a34:	90010391 	mulls	r1, r1, r3
40701a38:	930034d2 	movwls	r3, #1234	; 0x4d2
40701a3c:	90433521 	subls	r3, r3, r1, lsr #10
40701a40:	e59f1078 	ldr	r1, [pc, #120]	; 40701ac0 <start_svb+0x1f0>
40701a44:	e0833840 	add	r3, r3, r0, asr #16
40701a48:	e59f007c 	ldr	r0, [pc, #124]	; 40701acc <start_svb+0x1fc>
40701a4c:	e2822609 	add	r2, r2, #9437184	; 0x900000
40701a50:	e2822901 	add	r2, r2, #16384	; 0x4000
40701a54:	e5813158 	str	r3, [r1, #344]	; 0x158
40701a58:	e59f1070 	ldr	r1, [pc, #112]	; 40701ad0 <start_svb+0x200>
40701a5c:	e1a02282 	lsl	r2, r2, #5
40701a60:	e0231390 	mla	r3, r0, r3, r1
40701a64:	e1a03523 	lsr	r3, r3, #10
40701a68:	e5823004 	str	r3, [r2, #4]
40701a6c:	e3a03005 	mov	r3, #5
40701a70:	e582300c 	str	r3, [r2, #12]
40701a74:	e3a03000 	mov	r3, #0
40701a78:	e58d3000 	str	r3, [sp]
40701a7c:	e59d3000 	ldr	r3, [sp]
40701a80:	e3530dfa 	cmp	r3, #16000	; 0x3e80
40701a84:	3a000009 	bcc	40701ab0 <start_svb+0x1e0>
40701a88:	e28dd014 	add	sp, sp, #20
40701a8c:	e8bd8030 	pop	{r4, r5, pc}
40701a90:	e35300de 	cmp	r3, #222	; 0xde
40701a94:	93a02001 	movls	r2, #1
40701a98:	83a02000 	movhi	r2, #0
40701a9c:	e3510045 	cmp	r1, #69	; 0x45
40701aa0:	93a02000 	movls	r2, #0
40701aa4:	e3520000 	cmp	r2, #0
40701aa8:	12433004 	subne	r3, r3, #4
40701aac:	eaffffc7 	b	407019d0 <start_svb+0x100>
40701ab0:	e320f000 	nop	{0}
40701ab4:	e59d3000 	ldr	r3, [sp]
40701ab8:	e2833001 	add	r3, r3, #1
40701abc:	eaffffed 	b	40701a78 <start_svb+0x1a8>
40701ac0:	12020000 	.word	0x12020000
40701ac4:	12028000 	.word	0x12028000
40701ac8:	100a0000 	.word	0x100a0000
40701acc:	fffffe34 	.word	0xfffffe34
40701ad0:	0007b6c4 	.word	0x0007b6c4

40701ad4 <start_ddr_training>:
40701ad4:	e92d4df0 	push	{r4, r5, r6, r7, r8, sl, fp, lr}
40701ad8:	ebffff7c 	bl	407018d0 <start_svb>
40701adc:	e59f3154 	ldr	r3, [pc, #340]	; 40701c38 <start_ddr_training+0x164>
40701ae0:	e5937010 	ldr	r7, [r3, #16]
40701ae4:	e3c72020 	bic	r2, r7, #32
40701ae8:	e5832010 	str	r2, [r3, #16]
40701aec:	e2433906 	sub	r3, r3, #98304	; 0x18000
40701af0:	e5936198 	ldr	r6, [r3, #408]	; 0x198
40701af4:	e3862002 	orr	r2, r6, #2
40701af8:	e5832198 	str	r2, [r3, #408]	; 0x198
40701afc:	e320f000 	nop	{0}
40701b00:	e59f4134 	ldr	r4, [pc, #308]	; 40701c3c <start_ddr_training+0x168>
40701b04:	e3a00000 	mov	r0, #0
40701b08:	e5932198 	ldr	r2, [r3, #408]	; 0x198
40701b0c:	e59fa12c 	ldr	sl, [pc, #300]	; 40701c40 <start_ddr_training+0x16c>
40701b10:	e3c22001 	bic	r2, r2, #1
40701b14:	e5832198 	str	r2, [r3, #408]	; 0x198
40701b18:	e59450b0 	ldr	r5, [r4, #176]	; 0xb0
40701b1c:	e3c53102 	bic	r3, r5, #-2147483648	; 0x80000000
40701b20:	e58430b0 	str	r3, [r4, #176]	; 0xb0
40701b24:	eb0008e5 	bl	40703ec0 <ddr_pcode_training_if>
40701b28:	e3a00000 	mov	r0, #0
40701b2c:	eb0008e2 	bl	40703ebc <ddr_hw_training_if>
40701b30:	e3a00000 	mov	r0, #0
40701b34:	eb0008df 	bl	40703eb8 <ddr_sw_training_if>
40701b38:	e594222c 	ldr	r2, [r4, #556]	; 0x22c
40701b3c:	e594e21c 	ldr	lr, [r4, #540]	; 0x21c
40701b40:	e1a03004 	mov	r3, r4
40701b44:	e5948220 	ldr	r8, [r4, #544]	; 0x220
40701b48:	e594c224 	ldr	ip, [r4, #548]	; 0x224
40701b4c:	e1a0100e 	mov	r1, lr
40701b50:	e04cc002 	sub	ip, ip, r2
40701b54:	e2020003 	and	r0, r2, #3
40701b58:	e3500003 	cmp	r0, #3
40701b5c:	0a000009 	beq	40701b88 <start_ddr_training+0xb4>
40701b60:	e081100a 	add	r1, r1, sl
40701b64:	e2822001 	add	r2, r2, #1
40701b68:	e0880001 	add	r0, r8, r1
40701b6c:	e583222c 	str	r2, [r3, #556]	; 0x22c
40701b70:	e040000e 	sub	r0, r0, lr
40701b74:	e583121c 	str	r1, [r3, #540]	; 0x21c
40701b78:	e08c4002 	add	r4, ip, r2
40701b7c:	e5830220 	str	r0, [r3, #544]	; 0x220
40701b80:	e5834224 	str	r4, [r3, #548]	; 0x224
40701b84:	eafffff2 	b	40701b54 <start_ddr_training+0x80>
40701b88:	e59322ac 	ldr	r2, [r3, #684]	; 0x2ac
40701b8c:	e593e29c 	ldr	lr, [r3, #668]	; 0x29c
40701b90:	e59382a0 	ldr	r8, [r3, #672]	; 0x2a0
40701b94:	e593c2a4 	ldr	ip, [r3, #676]	; 0x2a4
40701b98:	e59fa0a0 	ldr	sl, [pc, #160]	; 40701c40 <start_ddr_training+0x16c>
40701b9c:	e1a0100e 	mov	r1, lr
40701ba0:	e59f3094 	ldr	r3, [pc, #148]	; 40701c3c <start_ddr_training+0x168>
40701ba4:	e04cc002 	sub	ip, ip, r2
40701ba8:	e2020003 	and	r0, r2, #3
40701bac:	e3500003 	cmp	r0, #3
40701bb0:	0a000009 	beq	40701bdc <start_ddr_training+0x108>
40701bb4:	e081100a 	add	r1, r1, sl
40701bb8:	e2822001 	add	r2, r2, #1
40701bbc:	e0880001 	add	r0, r8, r1
40701bc0:	e58322ac 	str	r2, [r3, #684]	; 0x2ac
40701bc4:	e040000e 	sub	r0, r0, lr
40701bc8:	e583129c 	str	r1, [r3, #668]	; 0x29c
40701bcc:	e08c4002 	add	r4, ip, r2
40701bd0:	e58302a0 	str	r0, [r3, #672]	; 0x2a0
40701bd4:	e58342a4 	str	r4, [r3, #676]	; 0x2a4
40701bd8:	eafffff2 	b	40701ba8 <start_ddr_training+0xd4>
40701bdc:	e5932070 	ldr	r2, [r3, #112]	; 0x70
40701be0:	e3821702 	orr	r1, r2, #524288	; 0x80000
40701be4:	e3c22702 	bic	r2, r2, #524288	; 0x80000
40701be8:	e5831070 	str	r1, [r3, #112]	; 0x70
40701bec:	e5832070 	str	r2, [r3, #112]	; 0x70
40701bf0:	e5932004 	ldr	r2, [r3, #4]
40701bf4:	e3821902 	orr	r1, r2, #32768	; 0x8000
40701bf8:	e3c22902 	bic	r2, r2, #32768	; 0x8000
40701bfc:	e5831004 	str	r1, [r3, #4]
40701c00:	e5832004 	str	r2, [r3, #4]
40701c04:	e59f202c 	ldr	r2, [pc, #44]	; 40701c38 <start_ddr_training+0x164>
40701c08:	e5827010 	str	r7, [r2, #16]
40701c0c:	e2422906 	sub	r2, r2, #98304	; 0x18000
40701c10:	e5826198 	str	r6, [r2, #408]	; 0x198
40701c14:	e3002401 	movw	r2, #1025	; 0x401
40701c18:	e58350b0 	str	r5, [r3, #176]	; 0xb0
40701c1c:	e593302c 	ldr	r3, [r3, #44]	; 0x2c
40701c20:	e203300f 	and	r3, r3, #15
40701c24:	e3530006 	cmp	r3, #6
40701c28:	e59f3014 	ldr	r3, [pc, #20]	; 40701c44 <start_ddr_training+0x170>
40701c2c:	e5832028 	str	r2, [r3, #40]	; 0x28
40701c30:	05832028 	streq	r2, [r3, #40]	; 0x28
40701c34:	e8bd8df0 	pop	{r4, r5, r6, r7, r8, sl, fp, pc}
40701c38:	12028000 	.word	0x12028000
40701c3c:	120dc000 	.word	0x120dc000
40701c40:	01010101 	.word	0x01010101
40701c44:	120d8000 	.word	0x120d8000

40701c48 <ddr_adjust_get_average>:
40701c48:	e5902060 	ldr	r2, [r0, #96]	; 0x60
40701c4c:	e5901040 	ldr	r1, [r0, #64]	; 0x40
40701c50:	e5903054 	ldr	r3, [r0, #84]	; 0x54
40701c54:	e5900050 	ldr	r0, [r0, #80]	; 0x50
40701c58:	e1a02502 	lsl	r2, r2, #10
40701c5c:	e3500002 	cmp	r0, #2
40701c60:	1a000004 	bne	40701c78 <ddr_adjust_get_average+0x30>
40701c64:	e2811f86 	add	r1, r1, #536	; 0x218
40701c68:	e0822001 	add	r2, r2, r1
40701c6c:	e7920383 	ldr	r0, [r2, r3, lsl #7]
40701c70:	e200007f 	and	r0, r0, #127	; 0x7f
40701c74:	e12fff1e 	bx	lr
40701c78:	e0823383 	add	r3, r2, r3, lsl #7
40701c7c:	e0833001 	add	r3, r3, r1
40701c80:	e593221c 	ldr	r2, [r3, #540]	; 0x21c
40701c84:	e5933220 	ldr	r3, [r3, #544]	; 0x220
40701c88:	e202007f 	and	r0, r2, #127	; 0x7f
40701c8c:	e203107f 	and	r1, r3, #127	; 0x7f
40701c90:	e0800001 	add	r0, r0, r1
40701c94:	e7e61452 	ubfx	r1, r2, #8, #7
40701c98:	e0800001 	add	r0, r0, r1
40701c9c:	e7e61852 	ubfx	r1, r2, #16, #7
40701ca0:	e0800001 	add	r0, r0, r1
40701ca4:	e7e62c52 	ubfx	r2, r2, #24, #7
40701ca8:	e0800002 	add	r0, r0, r2
40701cac:	e7e62453 	ubfx	r2, r3, #8, #7
40701cb0:	e0800002 	add	r0, r0, r2
40701cb4:	e7e62853 	ubfx	r2, r3, #16, #7
40701cb8:	e0800002 	add	r0, r0, r2
40701cbc:	e7e63c53 	ubfx	r3, r3, #24, #7
40701cc0:	e0800003 	add	r0, r0, r3
40701cc4:	e1a001a0 	lsr	r0, r0, #3
40701cc8:	e12fff1e 	bx	lr

40701ccc <ddr_read>:
40701ccc:	e5900000 	ldr	r0, [r0]
40701cd0:	e12fff1e 	bx	lr

40701cd4 <ddr_write>:
40701cd4:	e5810000 	str	r0, [r1]
40701cd8:	e12fff1e 	bx	lr

40701cdc <ddrtr_memcpy>:
40701cdc:	e2403001 	sub	r3, r0, #1
40701ce0:	e0812002 	add	r2, r1, r2
40701ce4:	e1510002 	cmp	r1, r2
40701ce8:	1a000000 	bne	40701cf0 <ddrtr_memcpy+0x14>
40701cec:	e12fff1e 	bx	lr
40701cf0:	e4d1c001 	ldrb	ip, [r1], #1
40701cf4:	e5e3c001 	strb	ip, [r3, #1]!
40701cf8:	eafffff9 	b	40701ce4 <ddrtr_memcpy+0x8>

40701cfc <ddrtr_memset>:
40701cfc:	e0802002 	add	r2, r0, r2
40701d00:	e1a03000 	mov	r3, r0
40701d04:	e1530002 	cmp	r3, r2
40701d08:	1a000000 	bne	40701d10 <ddrtr_memset+0x14>
40701d0c:	e12fff1e 	bx	lr
40701d10:	e4c31001 	strb	r1, [r3], #1
40701d14:	eafffffa 	b	40701d04 <ddrtr_memset+0x8>

40701d18 <ddr_training_by_dmc>:
40701d18:	e5903070 	ldr	r3, [r0, #112]	; 0x70
40701d1c:	e3530000 	cmp	r3, #0
40701d20:	1a000000 	bne	40701d28 <ddr_training_by_dmc+0x10>
40701d24:	ea0007f2 	b	40703cf4 <ddr_training_boot_func>
40701d28:	e3a00000 	mov	r0, #0
40701d2c:	e12fff1e 	bx	lr

40701d30 <ddr_training_by_rank>:
40701d30:	e92d41f0 	push	{r4, r5, r6, r7, r8, lr}
40701d34:	e3a05000 	mov	r5, #0
40701d38:	e5902040 	ldr	r2, [r0, #64]	; 0x40
40701d3c:	e1a04000 	mov	r4, r0
40701d40:	e5901060 	ldr	r1, [r0, #96]	; 0x60
40701d44:	e1a06005 	mov	r6, r5
40701d48:	e3a0703c 	mov	r7, #60	; 0x3c
40701d4c:	e3a0800c 	mov	r8, #12
40701d50:	e5923048 	ldr	r3, [r2, #72]	; 0x48
40701d54:	e3c3300f 	bic	r3, r3, #15
40701d58:	e1833001 	orr	r3, r3, r1
40701d5c:	e5823048 	str	r3, [r2, #72]	; 0x48
40701d60:	e594305c 	ldr	r3, [r4, #92]	; 0x5c
40701d64:	e0030397 	mul	r3, r7, r3
40701d68:	e0842003 	add	r2, r4, r3
40701d6c:	e5922008 	ldr	r2, [r2, #8]
40701d70:	e1520005 	cmp	r2, r5
40701d74:	8a000001 	bhi	40701d80 <ddr_training_by_rank+0x50>
40701d78:	e1a00006 	mov	r0, r6
40701d7c:	e8bd81f0 	pop	{r4, r5, r6, r7, r8, pc}
40701d80:	e0233598 	mla	r3, r8, r5, r3
40701d84:	e5845064 	str	r5, [r4, #100]	; 0x64
40701d88:	e1a00004 	mov	r0, r4
40701d8c:	e2855001 	add	r5, r5, #1
40701d90:	e0843003 	add	r3, r4, r3
40701d94:	e5932014 	ldr	r2, [r3, #20]
40701d98:	e5842044 	str	r2, [r4, #68]	; 0x44
40701d9c:	e593301c 	ldr	r3, [r3, #28]
40701da0:	e584304c 	str	r3, [r4, #76]	; 0x4c
40701da4:	ebffffdb 	bl	40701d18 <ddr_training_by_dmc>
40701da8:	e0866000 	add	r6, r6, r0
40701dac:	eaffffeb 	b	40701d60 <ddr_training_by_rank+0x30>

40701db0 <ddr_training_by_phy>:
40701db0:	e92d4df0 	push	{r4, r5, r6, r7, r8, sl, fp, lr}
40701db4:	e3a07001 	mov	r7, #1
40701db8:	e590305c 	ldr	r3, [r0, #92]	; 0x5c
40701dbc:	e3a0603c 	mov	r6, #60	; 0x3c
40701dc0:	e3a05000 	mov	r5, #0
40701dc4:	e1a04000 	mov	r4, r0
40701dc8:	e1a07317 	lsl	r7, r7, r3
40701dcc:	e1a08005 	mov	r8, r5
40701dd0:	e0230396 	mla	r3, r6, r3, r0
40701dd4:	e593a00c 	ldr	sl, [r3, #12]
40701dd8:	e155000a 	cmp	r5, sl
40701ddc:	1a000001 	bne	40701de8 <ddr_training_by_phy+0x38>
40701de0:	e1a00008 	mov	r0, r8
40701de4:	e8bd8df0 	pop	{r4, r5, r6, r7, r8, sl, fp, pc}
40701de8:	e594205c 	ldr	r2, [r4, #92]	; 0x5c
40701dec:	e2853005 	add	r3, r5, #5
40701df0:	e5845060 	str	r5, [r4, #96]	; 0x60
40701df4:	e0020296 	mul	r2, r6, r2
40701df8:	e0823183 	add	r3, r2, r3, lsl #3
40701dfc:	e0843003 	add	r3, r4, r3
40701e00:	e5933004 	ldr	r3, [r3, #4]
40701e04:	e1170003 	tst	r7, r3
40701e08:	e5843048 	str	r3, [r4, #72]	; 0x48
40701e0c:	0a000001 	beq	40701e18 <ddr_training_by_phy+0x68>
40701e10:	e2855001 	add	r5, r5, #1
40701e14:	eaffffef 	b	40701dd8 <ddr_training_by_phy+0x28>
40701e18:	e1a00004 	mov	r0, r4
40701e1c:	ebffffc3 	bl	40701d30 <ddr_training_by_rank>
40701e20:	e0888000 	add	r8, r8, r0
40701e24:	eafffff9 	b	40701e10 <ddr_training_by_phy+0x60>

40701e28 <ddr_training_all>:
40701e28:	e92d41f0 	push	{r4, r5, r6, r7, r8, lr}
40701e2c:	e3a04000 	mov	r4, #0
40701e30:	e1a05000 	mov	r5, r0
40701e34:	e1a06004 	mov	r6, r4
40701e38:	e3a0703c 	mov	r7, #60	; 0x3c
40701e3c:	e595303c 	ldr	r3, [r5, #60]	; 0x3c
40701e40:	e1530004 	cmp	r3, r4
40701e44:	8a000001 	bhi	40701e50 <ddr_training_all+0x28>
40701e48:	e1a00006 	mov	r0, r6
40701e4c:	e8bd81f0 	pop	{r4, r5, r6, r7, r8, pc}
40701e50:	e0030497 	mul	r3, r7, r4
40701e54:	e585405c 	str	r4, [r5, #92]	; 0x5c
40701e58:	e1a00005 	mov	r0, r5
40701e5c:	e2844001 	add	r4, r4, #1
40701e60:	e7953003 	ldr	r3, [r5, r3]
40701e64:	e5853040 	str	r3, [r5, #64]	; 0x40
40701e68:	ebffffd0 	bl	40701db0 <ddr_training_by_phy>
40701e6c:	e0866000 	add	r6, r6, r0
40701e70:	eafffff1 	b	40701e3c <ddr_training_all+0x14>

40701e74 <ddr_training_cfg_set_rank>:
40701e74:	e3a03001 	mov	r3, #1
40701e78:	e580300c 	str	r3, [r0, #12]
40701e7c:	e59f3030 	ldr	r3, [pc, #48]	; 40701eb4 <ddr_training_cfg_set_rank+0x40>
40701e80:	e59320a0 	ldr	r2, [r3, #160]	; 0xa0
40701e84:	e580202c 	str	r2, [r0, #44]	; 0x2c
40701e88:	e5932090 	ldr	r2, [r3, #144]	; 0x90
40701e8c:	e5802030 	str	r2, [r0, #48]	; 0x30
40701e90:	e59320a4 	ldr	r2, [r3, #164]	; 0xa4
40701e94:	e5802034 	str	r2, [r0, #52]	; 0x34
40701e98:	e5932094 	ldr	r2, [r3, #148]	; 0x94
40701e9c:	e5802038 	str	r2, [r0, #56]	; 0x38
40701ea0:	e5933094 	ldr	r3, [r3, #148]	; 0x94
40701ea4:	e3530000 	cmp	r3, #0
40701ea8:	13a03002 	movne	r3, #2
40701eac:	1580300c 	strne	r3, [r0, #12]
40701eb0:	e12fff1e 	bx	lr
40701eb4:	12020000 	.word	0x12020000

40701eb8 <ddr_training_cfg_set_phy>:
40701eb8:	e3a03001 	mov	r3, #1
40701ebc:	e580303c 	str	r3, [r0, #60]	; 0x3c
40701ec0:	e59f3010 	ldr	r3, [pc, #16]	; 40701ed8 <ddr_training_cfg_set_phy+0x20>
40701ec4:	e5803000 	str	r3, [r0]
40701ec8:	e593302c 	ldr	r3, [r3, #44]	; 0x2c
40701ecc:	e203300f 	and	r3, r3, #15
40701ed0:	e5803004 	str	r3, [r0, #4]
40701ed4:	e12fff1e 	bx	lr
40701ed8:	120dc000 	.word	0x120dc000

40701edc <ddr_training_set_timing>:
40701edc:	e30033e9 	movw	r3, #1001	; 0x3e9
40701ee0:	e2533001 	subs	r3, r3, #1
40701ee4:	1a000004 	bne	40701efc <ddr_training_set_timing+0x20>
40701ee8:	e30033e9 	movw	r3, #1001	; 0x3e9
40701eec:	e5801108 	str	r1, [r0, #264]	; 0x108
40701ef0:	e2533001 	subs	r3, r3, #1
40701ef4:	1a000002 	bne	40701f04 <ddr_training_set_timing+0x28>
40701ef8:	e12fff1e 	bx	lr
40701efc:	e320f000 	nop	{0}
40701f00:	eafffff6 	b	40701ee0 <ddr_training_set_timing+0x4>
40701f04:	e320f000 	nop	{0}
40701f08:	eafffff8 	b	40701ef0 <ddr_training_set_timing+0x14>

40701f0c <ddr_vref_set>:
40701f0c:	e5903050 	ldr	r3, [r0, #80]	; 0x50
40701f10:	e3530001 	cmp	r3, #1
40701f14:	1a000010 	bne	40701f5c <ddr_vref_set+0x50>
40701f18:	e5903060 	ldr	r3, [r0, #96]	; 0x60
40701f1c:	e5902040 	ldr	r2, [r0, #64]	; 0x40
40701f20:	e590c054 	ldr	ip, [r0, #84]	; 0x54
40701f24:	e2822f9d 	add	r2, r2, #628	; 0x274
40701f28:	e0822503 	add	r2, r2, r3, lsl #10
40701f2c:	e792338c 	ldr	r3, [r2, ip, lsl #7]
40701f30:	e3c3301f 	bic	r3, r3, #31
40701f34:	e1831001 	orr	r1, r3, r1
40701f38:	e782138c 	str	r1, [r2, ip, lsl #7]
40701f3c:	e5902060 	ldr	r2, [r0, #96]	; 0x60
40701f40:	e5903040 	ldr	r3, [r0, #64]	; 0x40
40701f44:	e2833f9d 	add	r3, r3, #628	; 0x274
40701f48:	e0833502 	add	r3, r3, r2, lsl #10
40701f4c:	e5902054 	ldr	r2, [r0, #84]	; 0x54
40701f50:	e2822001 	add	r2, r2, #1
40701f54:	e7831382 	str	r1, [r3, r2, lsl #7]
40701f58:	e12fff1e 	bx	lr
40701f5c:	e1a02000 	mov	r2, r0
40701f60:	e92d4070 	push	{r4, r5, r6, lr}
40701f64:	e1a04001 	mov	r4, r1
40701f68:	e5900044 	ldr	r0, [r0, #68]	; 0x44
40701f6c:	e5905108 	ldr	r5, [r0, #264]	; 0x108
40701f70:	e3c51eff 	bic	r1, r5, #4080	; 0xff0
40701f74:	e3c1100f 	bic	r1, r1, #15
40701f78:	ebffffd7 	bl	40701edc <ddr_training_set_timing>
40701f7c:	e5921040 	ldr	r1, [r2, #64]	; 0x40
40701f80:	e59130c0 	ldr	r3, [r1, #192]	; 0xc0
40701f84:	e3833102 	orr	r3, r3, #-2147483648	; 0x80000000
40701f88:	e58130c0 	str	r3, [r1, #192]	; 0xc0
40701f8c:	e5920040 	ldr	r0, [r2, #64]	; 0x40
40701f90:	e592c054 	ldr	ip, [r2, #84]	; 0x54
40701f94:	e2803e27 	add	r3, r0, #624	; 0x270
40701f98:	e59010c4 	ldr	r1, [r0, #196]	; 0xc4
40701f9c:	e793338c 	ldr	r3, [r3, ip, lsl #7]
40701fa0:	e381c102 	orr	ip, r1, #-2147483648	; 0x80000000
40701fa4:	e580c0c4 	str	ip, [r0, #196]	; 0xc4
40701fa8:	e5920040 	ldr	r0, [r2, #64]	; 0x40
40701fac:	e3c3303f 	bic	r3, r3, #63	; 0x3f
40701fb0:	e592c054 	ldr	ip, [r2, #84]	; 0x54
40701fb4:	e1833004 	orr	r3, r3, r4
40701fb8:	e2800e27 	add	r0, r0, #624	; 0x270
40701fbc:	e780338c 	str	r3, [r0, ip, lsl #7]
40701fc0:	e59f00f8 	ldr	r0, [pc, #248]	; 407020c0 <ddr_vref_set+0x1b4>
40701fc4:	e5923040 	ldr	r3, [r2, #64]	; 0x40
40701fc8:	e5830004 	str	r0, [r3, #4]
40701fcc:	e5923040 	ldr	r3, [r2, #64]	; 0x40
40701fd0:	e283c004 	add	ip, r3, #4
40701fd4:	e59c0000 	ldr	r0, [ip]
40701fd8:	e3100001 	tst	r0, #1
40701fdc:	1afffffc 	bne	40701fd4 <ddr_vref_set+0xc8>
40701fe0:	e3c11102 	bic	r1, r1, #-2147483648	; 0x80000000
40701fe4:	e58310c4 	str	r1, [r3, #196]	; 0xc4
40701fe8:	e5920040 	ldr	r0, [r2, #64]	; 0x40
40701fec:	e592c054 	ldr	ip, [r2, #84]	; 0x54
40701ff0:	e2803e27 	add	r3, r0, #624	; 0x270
40701ff4:	e59010c4 	ldr	r1, [r0, #196]	; 0xc4
40701ff8:	e793338c 	ldr	r3, [r3, ip, lsl #7]
40701ffc:	e381c102 	orr	ip, r1, #-2147483648	; 0x80000000
40702000:	e580c0c4 	str	ip, [r0, #196]	; 0xc4
40702004:	e5920040 	ldr	r0, [r2, #64]	; 0x40
40702008:	e3c3303f 	bic	r3, r3, #63	; 0x3f
4070200c:	e592c054 	ldr	ip, [r2, #84]	; 0x54
40702010:	e1833004 	orr	r3, r3, r4
40702014:	e2800e27 	add	r0, r0, #624	; 0x270
40702018:	e780338c 	str	r3, [r0, ip, lsl #7]
4070201c:	e59f009c 	ldr	r0, [pc, #156]	; 407020c0 <ddr_vref_set+0x1b4>
40702020:	e5923040 	ldr	r3, [r2, #64]	; 0x40
40702024:	e5830004 	str	r0, [r3, #4]
40702028:	e5923040 	ldr	r3, [r2, #64]	; 0x40
4070202c:	e283c004 	add	ip, r3, #4
40702030:	e59c0000 	ldr	r0, [ip]
40702034:	e3100001 	tst	r0, #1
40702038:	1afffffc 	bne	40702030 <ddr_vref_set+0x124>
4070203c:	e3c11102 	bic	r1, r1, #-2147483648	; 0x80000000
40702040:	e58310c4 	str	r1, [r3, #196]	; 0xc4
40702044:	e5921040 	ldr	r1, [r2, #64]	; 0x40
40702048:	e59130c0 	ldr	r3, [r1, #192]	; 0xc0
4070204c:	e3c33102 	bic	r3, r3, #-2147483648	; 0x80000000
40702050:	e58130c0 	str	r3, [r1, #192]	; 0xc0
40702054:	e5920040 	ldr	r0, [r2, #64]	; 0x40
40702058:	e592c054 	ldr	ip, [r2, #84]	; 0x54
4070205c:	e2801e27 	add	r1, r0, #624	; 0x270
40702060:	e59030c4 	ldr	r3, [r0, #196]	; 0xc4
40702064:	e791138c 	ldr	r1, [r1, ip, lsl #7]
40702068:	e383c102 	orr	ip, r3, #-2147483648	; 0x80000000
4070206c:	e580c0c4 	str	ip, [r0, #196]	; 0xc4
40702070:	e3c1103f 	bic	r1, r1, #63	; 0x3f
40702074:	e5920054 	ldr	r0, [r2, #84]	; 0x54
40702078:	e1814004 	orr	r4, r1, r4
4070207c:	e5921040 	ldr	r1, [r2, #64]	; 0x40
40702080:	e2811e27 	add	r1, r1, #624	; 0x270
40702084:	e7814380 	str	r4, [r1, r0, lsl #7]
40702088:	e59f0030 	ldr	r0, [pc, #48]	; 407020c0 <ddr_vref_set+0x1b4>
4070208c:	e5921040 	ldr	r1, [r2, #64]	; 0x40
40702090:	e5810004 	str	r0, [r1, #4]
40702094:	e5921040 	ldr	r1, [r2, #64]	; 0x40
40702098:	e281c004 	add	ip, r1, #4
4070209c:	e59c0000 	ldr	r0, [ip]
407020a0:	e3100001 	tst	r0, #1
407020a4:	1afffffc 	bne	4070209c <ddr_vref_set+0x190>
407020a8:	e3c33102 	bic	r3, r3, #-2147483648	; 0x80000000
407020ac:	e58130c4 	str	r3, [r1, #196]	; 0xc4
407020b0:	e1a01005 	mov	r1, r5
407020b4:	e5920044 	ldr	r0, [r2, #68]	; 0x44
407020b8:	e8bd4070 	pop	{r4, r5, r6, lr}
407020bc:	eaffff86 	b	40701edc <ddr_training_set_timing>
407020c0:	00040001 	.word	0x00040001

407020c4 <ddr_training_stat>:
407020c4:	e92d41f0 	push	{r4, r5, r6, r7, r8, lr}
407020c8:	e1a06003 	mov	r6, r3
407020cc:	e1a04000 	mov	r4, r0
407020d0:	e1a05001 	mov	r5, r1
407020d4:	e1a07002 	mov	r7, r2
407020d8:	eb00077d 	bl	40703ed4 <ddr_training_error>
407020dc:	e59f3040 	ldr	r3, [pc, #64]	; 40702124 <ddr_training_stat+0x60>
407020e0:	e59330b0 	ldr	r3, [r3, #176]	; 0xb0
407020e4:	e3530000 	cmp	r3, #0
407020e8:	18bd81f0 	popne	{r4, r5, r6, r7, r8, pc}
407020ec:	e3550000 	cmp	r5, #0
407020f0:	0a000004 	beq	40702108 <ddr_training_stat+0x44>
407020f4:	e59f302c 	ldr	r3, [pc, #44]	; 40702128 <ddr_training_stat+0x64>
407020f8:	e1550003 	cmp	r5, r3
407020fc:	03a05a01 	moveq	r5, #4096	; 0x1000
40702100:	13a05a02 	movne	r5, #8192	; 0x2000
40702104:	e1844005 	orr	r4, r4, r5
40702108:	e59f3014 	ldr	r3, [pc, #20]	; 40702124 <ddr_training_stat+0x60>
4070210c:	e3770001 	cmn	r7, #1
40702110:	11844c07 	orrne	r4, r4, r7, lsl #24
40702114:	e3760001 	cmn	r6, #1
40702118:	11844a06 	orrne	r4, r4, r6, lsl #20
4070211c:	e58340b0 	str	r4, [r3, #176]	; 0xb0
40702120:	e8bd81f0 	pop	{r4, r5, r6, r7, r8, pc}
40702124:	12020000 	.word	0x12020000
40702128:	120dc000 	.word	0x120dc000

4070212c <ddr_hw_training_process>:
4070212c:	e92d4df3 	push	{r0, r1, r4, r5, r6, r7, r8, sl, fp, lr}
40702130:	e2516000 	subs	r6, r1, #0
40702134:	e5905040 	ldr	r5, [r0, #64]	; 0x40
40702138:	e2853004 	add	r3, r5, #4
4070213c:	e58d3004 	str	r3, [sp, #4]
40702140:	e5952004 	ldr	r2, [r5, #4]
40702144:	1a000002 	bne	40702154 <ddr_hw_training_process+0x28>
40702148:	e3a00000 	mov	r0, #0
4070214c:	e28dd008 	add	sp, sp, #8
40702150:	e8bd8df0 	pop	{r4, r5, r6, r7, r8, sl, fp, pc}
40702154:	e3160a01 	tst	r6, #4096	; 0x1000
40702158:	e3863001 	orr	r3, r6, #1
4070215c:	e1833002 	orr	r3, r3, r2
40702160:	e1a07000 	mov	r7, r0
40702164:	e5853004 	str	r3, [r5, #4]
40702168:	0a000025 	beq	40702204 <ddr_hw_training_process+0xd8>
4070216c:	e590305c 	ldr	r3, [r0, #92]	; 0x5c
40702170:	e3a0203c 	mov	r2, #60	; 0x3c
40702174:	e3a08000 	mov	r8, #0
40702178:	e1a0a008 	mov	sl, r8
4070217c:	e0030392 	mul	r3, r2, r3
40702180:	e080b003 	add	fp, r0, r3
40702184:	e58d3000 	str	r3, [sp]
40702188:	e59b3008 	ldr	r3, [fp, #8]
4070218c:	e1530008 	cmp	r3, r8
40702190:	8a000003 	bhi	407021a4 <ddr_hw_training_process+0x78>
40702194:	e35a0000 	cmp	sl, #0
40702198:	0a000019 	beq	40702204 <ddr_hw_training_process+0xd8>
4070219c:	e3e00000 	mvn	r0, #0
407021a0:	eaffffe9 	b	4070214c <ddr_hw_training_process+0x20>
407021a4:	e59d2000 	ldr	r2, [sp]
407021a8:	e3a0300c 	mov	r3, #12
407021ac:	e3a04000 	mov	r4, #0
407021b0:	e0232893 	mla	r3, r3, r8, r2
407021b4:	e0873003 	add	r3, r7, r3
407021b8:	e5932014 	ldr	r2, [r3, #20]
407021bc:	e3a03002 	mov	r3, #2
407021c0:	e5823000 	str	r3, [r2]
407021c4:	e5923294 	ldr	r3, [r2, #660]	; 0x294
407021c8:	e2844001 	add	r4, r4, #1
407021cc:	e2133001 	ands	r3, r3, #1
407021d0:	0a000007 	beq	407021f4 <ddr_hw_training_process+0xc8>
407021d4:	e3740001 	cmn	r4, #1
407021d8:	1afffff9 	bne	407021c4 <ddr_hw_training_process+0x98>
407021dc:	e1a03004 	mov	r3, r4
407021e0:	e1a02004 	mov	r2, r4
407021e4:	e1a01004 	mov	r1, r4
407021e8:	e3a00010 	mov	r0, #16
407021ec:	ebffffb4 	bl	407020c4 <ddr_training_stat>
407021f0:	ea000000 	b	407021f8 <ddr_hw_training_process+0xcc>
407021f4:	e1a04003 	mov	r4, r3
407021f8:	e08aa004 	add	sl, sl, r4
407021fc:	e2888001 	add	r8, r8, #1
40702200:	eaffffe0 	b	40702188 <ddr_hw_training_process+0x5c>
40702204:	e3a04000 	mov	r4, #0
40702208:	e59d3004 	ldr	r3, [sp, #4]
4070220c:	e2844001 	add	r4, r4, #1
40702210:	e5933000 	ldr	r3, [r3]
40702214:	e3130001 	tst	r3, #1
40702218:	1a000003 	bne	4070222c <ddr_hw_training_process+0x100>
4070221c:	e5953008 	ldr	r3, [r5, #8]
40702220:	e3530000 	cmp	r3, #0
40702224:	0affffc7 	beq	40702148 <ddr_hw_training_process+0x1c>
40702228:	ea000001 	b	40702234 <ddr_hw_training_process+0x108>
4070222c:	e3740001 	cmn	r4, #1
40702230:	1afffff4 	bne	40702208 <ddr_hw_training_process+0xdc>
40702234:	e5953008 	ldr	r3, [r5, #8]
40702238:	e1a02006 	mov	r2, r6
4070223c:	e1a01005 	mov	r1, r5
40702240:	e3a00010 	mov	r0, #16
40702244:	ebffff9e 	bl	407020c4 <ddr_training_stat>
40702248:	eaffffd3 	b	4070219c <ddr_hw_training_process+0x70>

4070224c <ddr_training_check_bypass>:
4070224c:	e5903048 	ldr	r3, [r0, #72]	; 0x48
40702250:	e1110003 	tst	r1, r3
40702254:	13a00001 	movne	r0, #1
40702258:	03a00000 	moveq	r0, #0
4070225c:	e12fff1e 	bx	lr

40702260 <ddr_training_phy_disable>:
40702260:	e3a00000 	mov	r0, #0
40702264:	e12fff1e 	bx	lr

40702268 <ddr_training_switch_axi>:
40702268:	e590105c 	ldr	r1, [r0, #92]	; 0x5c
4070226c:	e3a0303c 	mov	r3, #60	; 0x3c
40702270:	e59fc054 	ldr	ip, [pc, #84]	; 407022cc <ddr_training_switch_axi+0x64>
40702274:	e0230193 	mla	r3, r3, r1, r0
40702278:	e59c2104 	ldr	r2, [ip, #260]	; 0x104
4070227c:	e3c2200f 	bic	r2, r2, #15
40702280:	e3822004 	orr	r2, r2, #4
40702284:	e5933004 	ldr	r3, [r3, #4]
40702288:	e3530006 	cmp	r3, #6
4070228c:	05903064 	ldreq	r3, [r0, #100]	; 0x64
40702290:	00831081 	addeq	r1, r3, r1, lsl #1
40702294:	e1822001 	orr	r2, r2, r1
40702298:	e58c2104 	str	r2, [ip, #260]	; 0x104
4070229c:	e59c3114 	ldr	r3, [ip, #276]	; 0x114
407022a0:	e3c3300f 	bic	r3, r3, #15
407022a4:	e3833004 	orr	r3, r3, #4
407022a8:	e1833001 	orr	r3, r3, r1
407022ac:	e58c3114 	str	r3, [ip, #276]	; 0x114
407022b0:	e5903060 	ldr	r3, [r0, #96]	; 0x60
407022b4:	e3530001 	cmp	r3, #1
407022b8:	05902044 	ldreq	r2, [r0, #68]	; 0x44
407022bc:	05923060 	ldreq	r3, [r2, #96]	; 0x60
407022c0:	03c33007 	biceq	r3, r3, #7
407022c4:	05823060 	streq	r3, [r2, #96]	; 0x60
407022c8:	e12fff1e 	bx	lr
407022cc:	120d0000 	.word	0x120d0000

407022d0 <ddr_phy_cfg_update>:
407022d0:	e5903070 	ldr	r3, [r0, #112]	; 0x70
407022d4:	e3832702 	orr	r2, r3, #524288	; 0x80000
407022d8:	e3c33702 	bic	r3, r3, #524288	; 0x80000
407022dc:	e5802070 	str	r2, [r0, #112]	; 0x70
407022e0:	e5803070 	str	r3, [r0, #112]	; 0x70
407022e4:	e5903004 	ldr	r3, [r0, #4]
407022e8:	e3832902 	orr	r2, r3, #32768	; 0x8000
407022ec:	e3c33902 	bic	r3, r3, #32768	; 0x8000
407022f0:	e5802004 	str	r2, [r0, #4]
407022f4:	e5803004 	str	r3, [r0, #4]
407022f8:	f57ff04f 	dsb	sy
407022fc:	e12fff1e 	bx	lr

40702300 <ddr_training_save_reg>:
40702300:	e92d41f0 	push	{r4, r5, r6, r7, r8, lr}
40702304:	e1a04001 	mov	r4, r1
40702308:	e5906044 	ldr	r6, [r0, #68]	; 0x44
4070230c:	e3017064 	movw	r7, #4196	; 0x1064
40702310:	e5905040 	ldr	r5, [r0, #64]	; 0x40
40702314:	e3520c01 	cmp	r2, #256	; 0x100
40702318:	e5961108 	ldr	r1, [r6, #264]	; 0x108
4070231c:	e5841000 	str	r1, [r4]
40702320:	e5963028 	ldr	r3, [r6, #40]	; 0x28
40702324:	e5843004 	str	r3, [r4, #4]
40702328:	e5953070 	ldr	r3, [r5, #112]	; 0x70
4070232c:	e5843010 	str	r3, [r4, #16]
40702330:	e7953007 	ldr	r3, [r5, r7]
40702334:	e5843014 	str	r3, [r4, #20]
40702338:	e7953007 	ldr	r3, [r5, r7]
4070233c:	e5843014 	str	r3, [r4, #20]
40702340:	0a000022 	beq	407023d0 <ddr_training_save_reg+0xd0>
40702344:	8a00001d 	bhi	407023c0 <ddr_training_save_reg+0xc0>
40702348:	e3520010 	cmp	r2, #16
4070234c:	1a000003 	bne	40702360 <ddr_training_save_reg+0x60>
40702350:	e3c11eff 	bic	r1, r1, #4080	; 0xff0
40702354:	e1a00006 	mov	r0, r6
40702358:	e3c1100f 	bic	r1, r1, #15
4070235c:	ebfffede 	bl	40701edc <ddr_training_set_timing>
40702360:	e5943004 	ldr	r3, [r4, #4]
40702364:	e1a00004 	mov	r0, r4
40702368:	e3c33001 	bic	r3, r3, #1
4070236c:	e5863028 	str	r3, [r6, #40]	; 0x28
40702370:	e5943010 	ldr	r3, [r4, #16]
40702374:	e3c33801 	bic	r3, r3, #65536	; 0x10000
40702378:	e5853070 	str	r3, [r5, #112]	; 0x70
4070237c:	e5953084 	ldr	r3, [r5, #132]	; 0x84
40702380:	e5843018 	str	r3, [r4, #24]
40702384:	e3c33407 	bic	r3, r3, #117440512	; 0x7000000
40702388:	e5853084 	str	r3, [r5, #132]	; 0x84
4070238c:	e59f305c 	ldr	r3, [pc, #92]	; 407023f0 <ddr_training_save_reg+0xf0>
40702390:	e5931104 	ldr	r1, [r3, #260]	; 0x104
40702394:	e584102c 	str	r1, [r4, #44]	; 0x2c
40702398:	e1a01002 	mov	r1, r2
4070239c:	e5933114 	ldr	r3, [r3, #276]	; 0x114
407023a0:	e5843030 	str	r3, [r4, #48]	; 0x30
407023a4:	e5963060 	ldr	r3, [r6, #96]	; 0x60
407023a8:	e5843034 	str	r3, [r4, #52]	; 0x34
407023ac:	eb0006fe 	bl	40703fac <ddr_training_save_reg_custom>
407023b0:	e1a00005 	mov	r0, r5
407023b4:	ebffffc5 	bl	407022d0 <ddr_phy_cfg_update>
407023b8:	f57ff04f 	dsb	sy
407023bc:	e8bd81f0 	pop	{r4, r5, r6, r7, r8, pc}
407023c0:	e3520601 	cmp	r2, #1048576	; 0x100000
407023c4:	0a000005 	beq	407023e0 <ddr_training_save_reg+0xe0>
407023c8:	e3520502 	cmp	r2, #8388608	; 0x800000
407023cc:	eaffffde 	b	4070234c <ddr_training_save_reg+0x4c>
407023d0:	e3c11eff 	bic	r1, r1, #4080	; 0xff0
407023d4:	e1a00006 	mov	r0, r6
407023d8:	e3c1100f 	bic	r1, r1, #15
407023dc:	ebfffebe 	bl	40701edc <ddr_training_set_timing>
407023e0:	e595302c 	ldr	r3, [r5, #44]	; 0x2c
407023e4:	e2133020 	ands	r3, r3, #32
407023e8:	07853007 	streq	r3, [r5, r7]
407023ec:	eaffffdb 	b	40702360 <ddr_training_save_reg+0x60>
407023f0:	120d0000 	.word	0x120d0000

407023f4 <ddr_training_restore_reg>:
407023f4:	e92d4070 	push	{r4, r5, r6, lr}
407023f8:	e1a02001 	mov	r2, r1
407023fc:	e5905044 	ldr	r5, [r0, #68]	; 0x44
40702400:	e5904040 	ldr	r4, [r0, #64]	; 0x40
40702404:	e5911000 	ldr	r1, [r1]
40702408:	e1a00005 	mov	r0, r5
4070240c:	ebfffeb2 	bl	40701edc <ddr_training_set_timing>
40702410:	e5923004 	ldr	r3, [r2, #4]
40702414:	e1a00002 	mov	r0, r2
40702418:	e5853028 	str	r3, [r5, #40]	; 0x28
4070241c:	e5923010 	ldr	r3, [r2, #16]
40702420:	e5843070 	str	r3, [r4, #112]	; 0x70
40702424:	e594302c 	ldr	r3, [r4, #44]	; 0x2c
40702428:	e3130020 	tst	r3, #32
4070242c:	05921014 	ldreq	r1, [r2, #20]
40702430:	03013064 	movweq	r3, #4196	; 0x1064
40702434:	07841003 	streq	r1, [r4, r3]
40702438:	e5923018 	ldr	r3, [r2, #24]
4070243c:	e5843084 	str	r3, [r4, #132]	; 0x84
40702440:	e59f3028 	ldr	r3, [pc, #40]	; 40702470 <ddr_training_restore_reg+0x7c>
40702444:	e592102c 	ldr	r1, [r2, #44]	; 0x2c
40702448:	e5831104 	str	r1, [r3, #260]	; 0x104
4070244c:	e5921030 	ldr	r1, [r2, #48]	; 0x30
40702450:	e5831114 	str	r1, [r3, #276]	; 0x114
40702454:	e5923034 	ldr	r3, [r2, #52]	; 0x34
40702458:	e5853060 	str	r3, [r5, #96]	; 0x60
4070245c:	eb0006d3 	bl	40703fb0 <ddr_training_restore_reg_custom>
40702460:	e1a00004 	mov	r0, r4
40702464:	ebffff99 	bl	407022d0 <ddr_phy_cfg_update>
40702468:	f57ff04f 	dsb	sy
4070246c:	e8bd8070 	pop	{r4, r5, r6, pc}
40702470:	120d0000 	.word	0x120d0000

40702474 <ddr_phy_set_dq_bdl>:
40702474:	e92d4010 	push	{r4, lr}
40702478:	e1a0e000 	mov	lr, r0
4070247c:	e59ec054 	ldr	ip, [lr, #84]	; 0x54
40702480:	e59e3060 	ldr	r3, [lr, #96]	; 0x60
40702484:	e59e2058 	ldr	r2, [lr, #88]	; 0x58
40702488:	e59ee050 	ldr	lr, [lr, #80]	; 0x50
4070248c:	e1a0c38c 	lsl	ip, ip, #7
40702490:	e1a03503 	lsl	r3, r3, #10
40702494:	e5900040 	ldr	r0, [r0, #64]	; 0x40
40702498:	e35e0002 	cmp	lr, #2
4070249c:	e2024007 	and	r4, r2, #7
407024a0:	e083300c 	add	r3, r3, ip
407024a4:	1a00000c 	bne	407024dc <ddr_phy_set_dq_bdl+0x68>
407024a8:	e3540003 	cmp	r4, #3
407024ac:	92833e21 	addls	r3, r3, #528	; 0x210
407024b0:	82833f85 	addhi	r3, r3, #532	; 0x214
407024b4:	e793c000 	ldr	ip, [r3, r0]
407024b8:	e1a02182 	lsl	r2, r2, #3
407024bc:	e2022018 	and	r2, r2, #24
407024c0:	e3a0e0ff 	mov	lr, #255	; 0xff
407024c4:	e201107f 	and	r1, r1, #127	; 0x7f
407024c8:	e1ccc21e 	bic	ip, ip, lr, lsl r2
407024cc:	e18c2211 	orr	r2, ip, r1, lsl r2
407024d0:	e7832000 	str	r2, [r3, r0]
407024d4:	e8bd4010 	pop	{r4, lr}
407024d8:	eaffff7c 	b	407022d0 <ddr_phy_cfg_update>
407024dc:	e3540003 	cmp	r4, #3
407024e0:	92833f87 	addls	r3, r3, #540	; 0x21c
407024e4:	82833e22 	addhi	r3, r3, #544	; 0x220
407024e8:	eafffff1 	b	407024b4 <ddr_phy_set_dq_bdl+0x40>

407024ec <ddr_phy_get_dq_bdl>:
407024ec:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
407024f0:	e5901054 	ldr	r1, [r0, #84]	; 0x54
407024f4:	e5903060 	ldr	r3, [r0, #96]	; 0x60
407024f8:	e590e050 	ldr	lr, [r0, #80]	; 0x50
407024fc:	e5902058 	ldr	r2, [r0, #88]	; 0x58
40702500:	e1a01381 	lsl	r1, r1, #7
40702504:	e35e0002 	cmp	lr, #2
40702508:	e1a03503 	lsl	r3, r3, #10
4070250c:	e202c007 	and	ip, r2, #7
40702510:	e0833001 	add	r3, r3, r1
40702514:	1a000009 	bne	40702540 <ddr_phy_get_dq_bdl+0x54>
40702518:	e35c0003 	cmp	ip, #3
4070251c:	92833e21 	addls	r3, r3, #528	; 0x210
40702520:	82833f85 	addhi	r3, r3, #532	; 0x214
40702524:	e5901040 	ldr	r1, [r0, #64]	; 0x40
40702528:	e1a02182 	lsl	r2, r2, #3
4070252c:	e2022018 	and	r2, r2, #24
40702530:	e7930001 	ldr	r0, [r3, r1]
40702534:	e1a00230 	lsr	r0, r0, r2
40702538:	e200007f 	and	r0, r0, #127	; 0x7f
4070253c:	e49df004 	pop	{pc}		; (ldr pc, [sp], #4)
40702540:	e35c0003 	cmp	ip, #3
40702544:	92833f87 	addls	r3, r3, #540	; 0x21c
40702548:	82833e22 	addhi	r3, r3, #544	; 0x220
4070254c:	eafffff4 	b	40702524 <ddr_phy_get_dq_bdl+0x38>

40702550 <ddr_rdqs_sync_rank_rdq>:
40702550:	e92d4070 	push	{r4, r5, r6, lr}
40702554:	e1a04000 	mov	r4, r0
40702558:	e5902060 	ldr	r2, [r0, #96]	; 0x60
4070255c:	e1a05001 	mov	r5, r1
40702560:	e5903040 	ldr	r3, [r0, #64]	; 0x40
40702564:	e3a06000 	mov	r6, #0
40702568:	e5900054 	ldr	r0, [r0, #84]	; 0x54
4070256c:	e2833f89 	add	r3, r3, #548	; 0x224
40702570:	e0833502 	add	r3, r3, r2, lsl #10
40702574:	e7932380 	ldr	r2, [r3, r0, lsl #7]
40702578:	e202107f 	and	r1, r2, #127	; 0x7f
4070257c:	e3c2207f 	bic	r2, r2, #127	; 0x7f
40702580:	e0851001 	add	r1, r5, r1
40702584:	e6e71011 	usat	r1, #7, r1
40702588:	e1822001 	orr	r2, r2, r1
4070258c:	e7832380 	str	r2, [r3, r0, lsl #7]
40702590:	e5846058 	str	r6, [r4, #88]	; 0x58
40702594:	e1a00004 	mov	r0, r4
40702598:	ebffffd3 	bl	407024ec <ddr_phy_get_dq_bdl>
4070259c:	e2866001 	add	r6, r6, #1
407025a0:	e0851000 	add	r1, r5, r0
407025a4:	e1a00004 	mov	r0, r4
407025a8:	e6e71011 	usat	r1, #7, r1
407025ac:	ebffffb0 	bl	40702474 <ddr_phy_set_dq_bdl>
407025b0:	e3560008 	cmp	r6, #8
407025b4:	1afffff5 	bne	40702590 <ddr_rdqs_sync_rank_rdq+0x40>
407025b8:	e8bd8070 	pop	{r4, r5, r6, pc}

407025bc <ddr_adjust_set_val>:
407025bc:	e92d41f0 	push	{r4, r5, r6, r7, r8, lr}
407025c0:	e1a04000 	mov	r4, r0
407025c4:	e5903050 	ldr	r3, [r0, #80]	; 0x50
407025c8:	e1a07001 	mov	r7, r1
407025cc:	e5902054 	ldr	r2, [r0, #84]	; 0x54
407025d0:	e3530001 	cmp	r3, #1
407025d4:	e5908060 	ldr	r8, [r0, #96]	; 0x60
407025d8:	e5903040 	ldr	r3, [r0, #64]	; 0x40
407025dc:	1a00001c 	bne	40702654 <ddr_adjust_set_val+0x98>
407025e0:	e2833f8b 	add	r3, r3, #556	; 0x22c
407025e4:	e7935382 	ldr	r5, [r3, r2, lsl #7]
407025e8:	e7936382 	ldr	r6, [r3, r2, lsl #7]
407025ec:	e7e86056 	ubfx	r6, r6, #0, #9
407025f0:	e0416006 	sub	r6, r1, r6
407025f4:	e1a01006 	mov	r1, r6
407025f8:	ebffffd4 	bl	40702550 <ddr_rdqs_sync_rank_rdq>
407025fc:	e594305c 	ldr	r3, [r4, #92]	; 0x5c
40702600:	e3a0203c 	mov	r2, #60	; 0x3c
40702604:	e0234392 	mla	r3, r2, r3, r4
40702608:	e593300c 	ldr	r3, [r3, #12]
4070260c:	e3530001 	cmp	r3, #1
40702610:	0a000005 	beq	4070262c <ddr_adjust_set_val+0x70>
40702614:	e2683001 	rsb	r3, r8, #1
40702618:	e1a01006 	mov	r1, r6
4070261c:	e5843060 	str	r3, [r4, #96]	; 0x60
40702620:	e1a00004 	mov	r0, r4
40702624:	ebffffc9 	bl	40702550 <ddr_rdqs_sync_rank_rdq>
40702628:	e5848060 	str	r8, [r4, #96]	; 0x60
4070262c:	e3c51f7f 	bic	r1, r5, #508	; 0x1fc
40702630:	e5943040 	ldr	r3, [r4, #64]	; 0x40
40702634:	e3c11003 	bic	r1, r1, #3
40702638:	e5942054 	ldr	r2, [r4, #84]	; 0x54
4070263c:	e1811007 	orr	r1, r1, r7
40702640:	e2833f8b 	add	r3, r3, #556	; 0x22c
40702644:	e7831382 	str	r1, [r3, r2, lsl #7]
40702648:	e5940040 	ldr	r0, [r4, #64]	; 0x40
4070264c:	e8bd41f0 	pop	{r4, r5, r6, r7, r8, lr}
40702650:	eaffff1e 	b	407022d0 <ddr_phy_cfg_update>
40702654:	e2833f8d 	add	r3, r3, #564	; 0x234
40702658:	e0833508 	add	r3, r3, r8, lsl #10
4070265c:	e7931382 	ldr	r1, [r3, r2, lsl #7]
40702660:	e3c11c1f 	bic	r1, r1, #7936	; 0x1f00
40702664:	e1811407 	orr	r1, r1, r7, lsl #8
40702668:	eafffff5 	b	40702644 <ddr_adjust_set_val+0x88>

4070266c <ddr_phy_get_byte_num>:
4070266c:	e5900050 	ldr	r0, [r0, #80]	; 0x50
40702670:	e1a001a0 	lsr	r0, r0, #3
40702674:	e2000006 	and	r0, r0, #6
40702678:	e3500004 	cmp	r0, #4
4070267c:	23a00004 	movcs	r0, #4
40702680:	e12fff1e 	bx	lr

40702684 <ddr_training_cfg_set_dmc>:
40702684:	e92d4010 	push	{r4, lr}
40702688:	e1a03000 	mov	r3, r0
4070268c:	e5902004 	ldr	r2, [r0, #4]
40702690:	e59f1078 	ldr	r1, [pc, #120]	; 40702710 <ddr_training_cfg_set_dmc+0x8c>
40702694:	e3520006 	cmp	r2, #6
40702698:	e59f2074 	ldr	r2, [pc, #116]	; 40702714 <ddr_training_cfg_set_dmc+0x90>
4070269c:	1a000012 	bne	407026ec <ddr_training_cfg_set_dmc+0x68>
407026a0:	e3a00002 	mov	r0, #2
407026a4:	e5830008 	str	r0, [r3, #8]
407026a8:	e59110a8 	ldr	r1, [r1, #168]	; 0xa8
407026ac:	e5832014 	str	r2, [r3, #20]
407026b0:	e6ff0071 	uxth	r0, r1
407026b4:	e583001c 	str	r0, [r3, #28]
407026b8:	e1a00002 	mov	r0, r2
407026bc:	ebffffea 	bl	4070266c <ddr_phy_get_byte_num>
407026c0:	e5830018 	str	r0, [r3, #24]
407026c4:	e1a01821 	lsr	r1, r1, #16
407026c8:	e5832020 	str	r2, [r3, #32]
407026cc:	e1a00002 	mov	r0, r2
407026d0:	e5831028 	str	r1, [r3, #40]	; 0x28
407026d4:	ebffffe4 	bl	4070266c <ddr_phy_get_byte_num>
407026d8:	e5932018 	ldr	r2, [r3, #24]
407026dc:	e5830024 	str	r0, [r3, #36]	; 0x24
407026e0:	e0820000 	add	r0, r2, r0
407026e4:	e5830010 	str	r0, [r3, #16]
407026e8:	e8bd8010 	pop	{r4, pc}
407026ec:	e3a00001 	mov	r0, #1
407026f0:	e5832014 	str	r2, [r3, #20]
407026f4:	e5830008 	str	r0, [r3, #8]
407026f8:	e1a00002 	mov	r0, r2
407026fc:	e59110a8 	ldr	r1, [r1, #168]	; 0xa8
40702700:	e583101c 	str	r1, [r3, #28]
40702704:	ebffffd8 	bl	4070266c <ddr_phy_get_byte_num>
40702708:	e5830018 	str	r0, [r3, #24]
4070270c:	eafffff4 	b	407026e4 <ddr_training_cfg_set_dmc+0x60>
40702710:	12020000 	.word	0x12020000
40702714:	120d8000 	.word	0x120d8000

40702718 <ddr_training_cfg_init>:
40702718:	e92d4010 	push	{r4, lr}
4070271c:	e3a02078 	mov	r2, #120	; 0x78
40702720:	e1a04000 	mov	r4, r0
40702724:	e3a01000 	mov	r1, #0
40702728:	ebfffd73 	bl	40701cfc <ddrtr_memset>
4070272c:	e1a00004 	mov	r0, r4
40702730:	ebfffde0 	bl	40701eb8 <ddr_training_cfg_set_phy>
40702734:	e1a00004 	mov	r0, r4
40702738:	ebffffd1 	bl	40702684 <ddr_training_cfg_set_dmc>
4070273c:	e1a00004 	mov	r0, r4
40702740:	e8bd4010 	pop	{r4, lr}
40702744:	eafffdca 	b	40701e74 <ddr_training_cfg_set_rank>

40702748 <ddr_ddrt_init>:
40702748:	e92d41f0 	push	{r4, r5, r6, r7, r8, lr}
4070274c:	e1a05000 	mov	r5, r0
40702750:	e5906060 	ldr	r6, [r0, #96]	; 0x60
40702754:	e1a07001 	mov	r7, r1
40702758:	e3560001 	cmp	r6, #1
4070275c:	13a06000 	movne	r6, #0
40702760:	1a00000b 	bne	40702794 <ddr_ddrt_init+0x4c>
40702764:	e5903044 	ldr	r3, [r0, #68]	; 0x44
40702768:	e5932050 	ldr	r2, [r3, #80]	; 0x50
4070276c:	e5933060 	ldr	r3, [r3, #96]	; 0x60
40702770:	e7e12252 	ubfx	r2, r2, #4, #2
40702774:	e2030007 	and	r0, r3, #7
40702778:	e2800015 	add	r0, r0, #21
4070277c:	e0800002 	add	r0, r0, r2
40702780:	e7e12453 	ubfx	r2, r3, #8, #2
40702784:	e0800002 	add	r0, r0, r2
40702788:	e7e23253 	ubfx	r3, r3, #4, #3
4070278c:	e0800003 	add	r0, r0, r3
40702790:	e1a06016 	lsl	r6, r6, r0
40702794:	e5953044 	ldr	r3, [r5, #68]	; 0x44
40702798:	e3002152 	movw	r2, #338	; 0x152
4070279c:	e59f40a0 	ldr	r4, [pc, #160]	; 40702844 <ddr_ddrt_init+0xfc>
407027a0:	e5933050 	ldr	r3, [r3, #80]	; 0x50
407027a4:	e7e13253 	ubfx	r3, r3, #4, #2
407027a8:	e2433001 	sub	r3, r3, #1
407027ac:	e1823603 	orr	r3, r2, r3, lsl #12
407027b0:	e584300c 	str	r3, [r4, #12]
407027b4:	e3a03101 	mov	r3, #1073741824	; 0x40000000
407027b8:	e584301c 	str	r3, [r4, #28]
407027bc:	eb0005c2 	bl	40703ecc <ddr_ddrt_get_test_addr>
407027c0:	e59f3080 	ldr	r3, [pc, #128]	; 40702848 <ddr_ddrt_init+0x100>
407027c4:	e3570001 	cmp	r7, #1
407027c8:	e0860000 	add	r0, r6, r0
407027cc:	e5840020 	str	r0, [r4, #32]
407027d0:	e5843038 	str	r3, [r4, #56]	; 0x38
407027d4:	1a000008 	bne	407027fc <ddr_ddrt_init+0xb4>
407027d8:	e3a03043 	mov	r3, #67	; 0x43
407027dc:	e5843008 	str	r3, [r4, #8]
407027e0:	e3a03000 	mov	r3, #0
407027e4:	e5843010 	str	r3, [r4, #16]
407027e8:	e5843014 	str	r3, [r4, #20]
407027ec:	e5843018 	str	r3, [r4, #24]
407027f0:	e59f3054 	ldr	r3, [pc, #84]	; 4070284c <ddr_ddrt_init+0x104>
407027f4:	e5843030 	str	r3, [r4, #48]	; 0x30
407027f8:	e8bd81f0 	pop	{r4, r5, r6, r7, r8, pc}
407027fc:	e3a0304f 	mov	r3, #79	; 0x4f
40702800:	e5843008 	str	r3, [r4, #8]
40702804:	e595105c 	ldr	r1, [r5, #92]	; 0x5c
40702808:	e3a0203c 	mov	r2, #60	; 0x3c
4070280c:	e5953064 	ldr	r3, [r5, #100]	; 0x64
40702810:	e0020192 	mul	r2, r2, r1
40702814:	e3a0100c 	mov	r1, #12
40702818:	e0232391 	mla	r3, r1, r3, r2
4070281c:	e0855003 	add	r5, r5, r3
40702820:	e595301c 	ldr	r3, [r5, #28]
40702824:	e5843030 	str	r3, [r4, #48]	; 0x30
40702828:	e3a0307f 	mov	r3, #127	; 0x7f
4070282c:	e5843010 	str	r3, [r4, #16]
40702830:	e3e03000 	mvn	r3, #0
40702834:	e5843014 	str	r3, [r4, #20]
40702838:	e3a03000 	mov	r3, #0
4070283c:	e5843018 	str	r3, [r4, #24]
40702840:	e8bd81f0 	pop	{r4, r5, r6, r7, r8, pc}
40702844:	11330000 	.word	0x11330000
40702848:	6d6d6d6d 	.word	0x6d6d6d6d
4070284c:	55aa55aa 	.word	0x55aa55aa

40702850 <ddr_ddrt_test>:
40702850:	e59f3108 	ldr	r3, [pc, #264]	; 40702960 <ddr_ddrt_test+0x110>
40702854:	e380c001 	orr	ip, r0, #1
40702858:	e92d4010 	push	{r4, lr}
4070285c:	e583c000 	str	ip, [r3]
40702860:	e3a0c000 	mov	ip, #0
40702864:	e583c004 	str	ip, [r3, #4]
40702868:	f57ff04f 	dsb	sy
4070286c:	e59f40f0 	ldr	r4, [pc, #240]	; 40702964 <ddr_ddrt_test+0x114>
40702870:	e593e004 	ldr	lr, [r3, #4]
40702874:	e28cc001 	add	ip, ip, #1
40702878:	e31e0001 	tst	lr, #1
4070287c:	1a000008 	bne	407028a4 <ddr_ddrt_test+0x54>
40702880:	e15c0004 	cmp	ip, r4
40702884:	1afffff9 	bne	40702870 <ddr_ddrt_test+0x20>
40702888:	e3e03000 	mvn	r3, #0
4070288c:	e3a01000 	mov	r1, #0
40702890:	e1a02003 	mov	r2, r3
40702894:	e3a00008 	mov	r0, #8
40702898:	ebfffe09 	bl	407020c4 <ddr_training_stat>
4070289c:	e3e02000 	mvn	r2, #0
407028a0:	ea000019 	b	4070290c <ddr_ddrt_test+0xbc>
407028a4:	e15c0004 	cmp	ip, r4
407028a8:	0afffff6 	beq	40702888 <ddr_ddrt_test+0x38>
407028ac:	e2000c03 	and	r0, r0, #768	; 0x300
407028b0:	e3500c02 	cmp	r0, #512	; 0x200
407028b4:	0a000027 	beq	40702958 <ddr_ddrt_test+0x108>
407028b8:	e21ee002 	ands	lr, lr, #2
407028bc:	1a000025 	bne	40702958 <ddr_ddrt_test+0x108>
407028c0:	e3720001 	cmn	r2, #1
407028c4:	0a000012 	beq	40702914 <ddr_ddrt_test+0xc4>
407028c8:	e5930080 	ldr	r0, [r3, #128]	; 0x80
407028cc:	e3a0c001 	mov	ip, #1
407028d0:	e0823181 	add	r3, r2, r1, lsl #3
407028d4:	e010331c 	ands	r3, r0, ip, lsl r3
407028d8:	1affffef 	bne	4070289c <ddr_ddrt_test+0x4c>
407028dc:	e3520003 	cmp	r2, #3
407028e0:	c2423004 	subgt	r3, r2, #4
407028e4:	d1a03182 	lslle	r3, r2, #3
407028e8:	e1a02122 	lsr	r2, r2, #2
407028ec:	e0821081 	add	r1, r2, r1, lsl #1
407028f0:	e59f2070 	ldr	r2, [pc, #112]	; 40702968 <ddr_ddrt_test+0x118>
407028f4:	c1a03183 	lslgt	r3, r3, #3
407028f8:	e7922101 	ldr	r2, [r2, r1, lsl #2]
407028fc:	e3a010ff 	mov	r1, #255	; 0xff
40702900:	e0123311 	ands	r3, r2, r1, lsl r3
40702904:	13e02000 	mvnne	r2, #0
40702908:	03a02000 	moveq	r2, #0
4070290c:	e1a00002 	mov	r0, r2
40702910:	e8bd8010 	pop	{r4, pc}
40702914:	e3710001 	cmn	r1, #1
40702918:	01a0200e 	moveq	r2, lr
4070291c:	0afffffa 	beq	4070290c <ddr_ddrt_test+0xbc>
40702920:	e5930080 	ldr	r0, [r3, #128]	; 0x80
40702924:	e3a0c0ff 	mov	ip, #255	; 0xff
40702928:	e1a03181 	lsl	r3, r1, #3
4070292c:	e010331c 	ands	r3, r0, ip, lsl r3
40702930:	1afffff5 	bne	4070290c <ddr_ddrt_test+0xbc>
40702934:	e59f302c 	ldr	r3, [pc, #44]	; 40702968 <ddr_ddrt_test+0x118>
40702938:	e7932181 	ldr	r2, [r3, r1, lsl #3]
4070293c:	e1a01081 	lsl	r1, r1, #1
40702940:	e2811001 	add	r1, r1, #1
40702944:	e7933101 	ldr	r3, [r3, r1, lsl #2]
40702948:	e1720003 	cmn	r2, r3
4070294c:	13e02000 	mvnne	r2, #0
40702950:	03a02000 	moveq	r2, #0
40702954:	eaffffec 	b	4070290c <ddr_ddrt_test+0xbc>
40702958:	e3a02000 	mov	r2, #0
4070295c:	eaffffea 	b	4070290c <ddr_ddrt_test+0xbc>
40702960:	11330000 	.word	0x11330000
40702964:	000f4240 	.word	0x000f4240
40702968:	11330060 	.word	0x11330060

4070296c <ddr_dataeye_check_dq>:
4070296c:	e590306c 	ldr	r3, [r0, #108]	; 0x6c
40702970:	e3530001 	cmp	r3, #1
40702974:	1a000018 	bne	407029dc <ddr_dataeye_check_dq+0x70>
40702978:	e92d4070 	push	{r4, r5, r6, lr}
4070297c:	e1a04000 	mov	r4, r0
40702980:	e5903064 	ldr	r3, [r0, #100]	; 0x64
40702984:	e5905054 	ldr	r5, [r0, #84]	; 0x54
40702988:	e3a00000 	mov	r0, #0
4070298c:	e59f6058 	ldr	r6, [pc, #88]	; 407029ec <ddr_dataeye_check_dq+0x80>
40702990:	e1a03083 	lsl	r3, r3, #1
40702994:	e1550003 	cmp	r5, r3
40702998:	20455003 	subcs	r5, r5, r3
4070299c:	e5860030 	str	r0, [r6, #48]	; 0x30
407029a0:	e5942058 	ldr	r2, [r4, #88]	; 0x58
407029a4:	e1a01005 	mov	r1, r5
407029a8:	ebffffa8 	bl	40702850 <ddr_ddrt_test>
407029ac:	e3500000 	cmp	r0, #0
407029b0:	1a00000b 	bne	407029e4 <ddr_dataeye_check_dq+0x78>
407029b4:	e594304c 	ldr	r3, [r4, #76]	; 0x4c
407029b8:	e1a01005 	mov	r1, r5
407029bc:	e3a00a02 	mov	r0, #8192	; 0x2000
407029c0:	e5863030 	str	r3, [r6, #48]	; 0x30
407029c4:	e5942058 	ldr	r2, [r4, #88]	; 0x58
407029c8:	ebffffa0 	bl	40702850 <ddr_ddrt_test>
407029cc:	e2900000 	adds	r0, r0, #0
407029d0:	13a00001 	movne	r0, #1
407029d4:	e2600000 	rsb	r0, r0, #0
407029d8:	e8bd8070 	pop	{r4, r5, r6, pc}
407029dc:	e3a00000 	mov	r0, #0
407029e0:	e12fff1e 	bx	lr
407029e4:	e3e00000 	mvn	r0, #0
407029e8:	e8bd8070 	pop	{r4, r5, r6, pc}
407029ec:	11330000 	.word	0x11330000

407029f0 <ddr_dataeye_search_dq>:
407029f0:	e92d4df3 	push	{r0, r1, r4, r5, r6, r7, r8, sl, fp, lr}
407029f4:	e1a06000 	mov	r6, r0
407029f8:	e59d5028 	ldr	r5, [sp, #40]	; 0x28
407029fc:	e1a0a001 	mov	sl, r1
40702a00:	e1a0b002 	mov	fp, r2
40702a04:	e1a08003 	mov	r8, r3
40702a08:	e04a4006 	sub	r4, sl, r6
40702a0c:	e1a00005 	mov	r0, r5
40702a10:	e08640a4 	add	r4, r6, r4, lsr #1
40702a14:	e1a01004 	mov	r1, r4
40702a18:	ebfffe95 	bl	40702474 <ddr_phy_set_dq_bdl>
40702a1c:	e1a00005 	mov	r0, r5
40702a20:	ebffffd1 	bl	4070296c <ddr_dataeye_check_dq>
40702a24:	e3580002 	cmp	r8, #2
40702a28:	0a000009 	beq	40702a54 <ddr_dataeye_search_dq+0x64>
40702a2c:	e3580004 	cmp	r8, #4
40702a30:	0a00000f 	beq	40702a74 <ddr_dataeye_search_dq+0x84>
40702a34:	e3580001 	cmp	r8, #1
40702a38:	03a07006 	moveq	r7, #6
40702a3c:	13a07000 	movne	r7, #0
40702a40:	e3500000 	cmp	r0, #0
40702a44:	1a00000f 	bne	40702a88 <ddr_dataeye_search_dq+0x98>
40702a48:	e58b4000 	str	r4, [fp]
40702a4c:	e28dd008 	add	sp, sp, #8
40702a50:	e8bd8df0 	pop	{r4, r5, r6, r7, r8, sl, fp, pc}
40702a54:	e3500000 	cmp	r0, #0
40702a58:	1a000009 	bne	40702a84 <ddr_dataeye_search_dq+0x94>
40702a5c:	e1a01006 	mov	r1, r6
40702a60:	e1a00005 	mov	r0, r5
40702a64:	ebfffe82 	bl	40702474 <ddr_phy_set_dq_bdl>
40702a68:	e1a00005 	mov	r0, r5
40702a6c:	ebffffbe 	bl	4070296c <ddr_dataeye_check_dq>
40702a70:	eafffff4 	b	40702a48 <ddr_dataeye_search_dq+0x58>
40702a74:	e3500000 	cmp	r0, #0
40702a78:	1a000011 	bne	40702ac4 <ddr_dataeye_search_dq+0xd4>
40702a7c:	e1a0100a 	mov	r1, sl
40702a80:	eafffff6 	b	40702a60 <ddr_dataeye_search_dq+0x70>
40702a84:	e3a07004 	mov	r7, #4
40702a88:	e154000a 	cmp	r4, sl
40702a8c:	11560004 	cmpne	r6, r4
40702a90:	0affffed 	beq	40702a4c <ddr_dataeye_search_dq+0x5c>
40702a94:	e3170002 	tst	r7, #2
40702a98:	0a000005 	beq	40702ab4 <ddr_dataeye_search_dq+0xc4>
40702a9c:	e58d5000 	str	r5, [sp]
40702aa0:	e1a03008 	mov	r3, r8
40702aa4:	e1a0200b 	mov	r2, fp
40702aa8:	e1a01004 	mov	r1, r4
40702aac:	e1a00006 	mov	r0, r6
40702ab0:	ebffffce 	bl	407029f0 <ddr_dataeye_search_dq>
40702ab4:	e3170004 	tst	r7, #4
40702ab8:	e1a06004 	mov	r6, r4
40702abc:	0affffe2 	beq	40702a4c <ddr_dataeye_search_dq+0x5c>
40702ac0:	eaffffd0 	b	40702a08 <ddr_dataeye_search_dq+0x18>
40702ac4:	e3a07002 	mov	r7, #2
40702ac8:	eaffffee 	b	40702a88 <ddr_dataeye_search_dq+0x98>

40702acc <ddr_dataeye_deskew>:
40702acc:	e92d4df0 	push	{r4, r5, r6, r7, r8, sl, fp, lr}
40702ad0:	e3a05000 	mov	r5, #0
40702ad4:	e5903054 	ldr	r3, [r0, #84]	; 0x54
40702ad8:	e24dd028 	sub	sp, sp, #40	; 0x28
40702adc:	e1a04000 	mov	r4, r0
40702ae0:	e1a06001 	mov	r6, r1
40702ae4:	e1a08005 	mov	r8, r5
40702ae8:	e1a0a005 	mov	sl, r5
40702aec:	e58d3008 	str	r3, [sp, #8]
40702af0:	e1a03183 	lsl	r3, r3, #3
40702af4:	e5815100 	str	r5, [r1, #256]	; 0x100
40702af8:	e58d300c 	str	r3, [sp, #12]
40702afc:	e59d300c 	ldr	r3, [sp, #12]
40702b00:	e1a00004 	mov	r0, r4
40702b04:	e5845058 	str	r5, [r4, #88]	; 0x58
40702b08:	e0853003 	add	r3, r5, r3
40702b0c:	e58d3010 	str	r3, [sp, #16]
40702b10:	ebfffe75 	bl	407024ec <ddr_phy_get_dq_bdl>
40702b14:	e5943054 	ldr	r3, [r4, #84]	; 0x54
40702b18:	e5947058 	ldr	r7, [r4, #88]	; 0x58
40702b1c:	e0877183 	add	r7, r7, r3, lsl #3
40702b20:	e58d0014 	str	r0, [sp, #20]
40702b24:	e1a00004 	mov	r0, r4
40702b28:	ebfffe6f 	bl	407024ec <ddr_phy_get_dq_bdl>
40702b2c:	e58d001c 	str	r0, [sp, #28]
40702b30:	e1a0b000 	mov	fp, r0
40702b34:	e1a00004 	mov	r0, r4
40702b38:	ebffff8b 	bl	4070296c <ddr_dataeye_check_dq>
40702b3c:	e3500000 	cmp	r0, #0
40702b40:	0a000037 	beq	40702c24 <ddr_dataeye_deskew+0x158>
40702b44:	e28d2028 	add	r2, sp, #40	; 0x28
40702b48:	e3e03000 	mvn	r3, #0
40702b4c:	e3a0107f 	mov	r1, #127	; 0x7f
40702b50:	e3a00000 	mov	r0, #0
40702b54:	e522300c 	str	r3, [r2, #-12]!
40702b58:	e3a03001 	mov	r3, #1
40702b5c:	e58d4000 	str	r4, [sp]
40702b60:	ebffffa2 	bl	407029f0 <ddr_dataeye_search_dq>
40702b64:	e59d301c 	ldr	r3, [sp, #28]
40702b68:	e3730001 	cmn	r3, #1
40702b6c:	1a00002c 	bne	40702c24 <ddr_dataeye_deskew+0x158>
40702b70:	e0862107 	add	r2, r6, r7, lsl #2
40702b74:	e3a03000 	mov	r3, #0
40702b78:	e1a0100b 	mov	r1, fp
40702b7c:	e7863107 	str	r3, [r6, r7, lsl #2]
40702b80:	e1a00004 	mov	r0, r4
40702b84:	e5823080 	str	r3, [r2, #128]	; 0x80
40702b88:	ebfffe39 	bl	40702474 <ddr_phy_set_dq_bdl>
40702b8c:	e59d3010 	ldr	r3, [sp, #16]
40702b90:	e2833020 	add	r3, r3, #32
40702b94:	e7967103 	ldr	r7, [r6, r3, lsl #2]
40702b98:	e1a0b827 	lsr	fp, r7, #16
40702b9c:	e35b0007 	cmp	fp, #7
40702ba0:	8a000057 	bhi	40702d04 <ddr_dataeye_deskew+0x238>
40702ba4:	e35a0000 	cmp	sl, #0
40702ba8:	02455001 	subeq	r5, r5, #1
40702bac:	03a0a001 	moveq	sl, #1
40702bb0:	0a000009 	beq	40702bdc <ddr_dataeye_deskew+0x110>
40702bb4:	e35b0000 	cmp	fp, #0
40702bb8:	1a000051 	bne	40702d04 <ddr_dataeye_deskew+0x238>
40702bbc:	e59d1014 	ldr	r1, [sp, #20]
40702bc0:	e1a00004 	mov	r0, r4
40702bc4:	ebfffe2a 	bl	40702474 <ddr_phy_set_dq_bdl>
40702bc8:	e1a03005 	mov	r3, r5
40702bcc:	e59d2008 	ldr	r2, [sp, #8]
40702bd0:	e3a00040 	mov	r0, #64	; 0x40
40702bd4:	e5941040 	ldr	r1, [r4, #64]	; 0x40
40702bd8:	ebfffd39 	bl	407020c4 <ddr_training_stat>
40702bdc:	e2855001 	add	r5, r5, #1
40702be0:	e3550007 	cmp	r5, #7
40702be4:	daffffc4 	ble	40702afc <ddr_dataeye_deskew+0x30>
40702be8:	e5943050 	ldr	r3, [r4, #80]	; 0x50
40702bec:	e3530002 	cmp	r3, #2
40702bf0:	1a000006 	bne	40702c10 <ddr_dataeye_deskew+0x144>
40702bf4:	e5942060 	ldr	r2, [r4, #96]	; 0x60
40702bf8:	e7e681d8 	ubfx	r8, r8, #3, #7
40702bfc:	e5943040 	ldr	r3, [r4, #64]	; 0x40
40702c00:	e2833f86 	add	r3, r3, #536	; 0x218
40702c04:	e0833502 	add	r3, r3, r2, lsl #10
40702c08:	e59d2008 	ldr	r2, [sp, #8]
40702c0c:	e7838382 	str	r8, [r3, r2, lsl #7]
40702c10:	e5940040 	ldr	r0, [r4, #64]	; 0x40
40702c14:	ebfffdad 	bl	407022d0 <ddr_phy_cfg_update>
40702c18:	e3a00000 	mov	r0, #0
40702c1c:	e28dd028 	add	sp, sp, #40	; 0x28
40702c20:	e8bd8df0 	pop	{r4, r5, r6, r7, r8, sl, fp, pc}
40702c24:	e59d101c 	ldr	r1, [sp, #28]
40702c28:	e3a03002 	mov	r3, #2
40702c2c:	e58d4000 	str	r4, [sp]
40702c30:	e28d2020 	add	r2, sp, #32
40702c34:	e3a00000 	mov	r0, #0
40702c38:	e58d1020 	str	r1, [sp, #32]
40702c3c:	ebffff6b 	bl	407029f0 <ddr_dataeye_search_dq>
40702c40:	e59d1020 	ldr	r1, [sp, #32]
40702c44:	e3510000 	cmp	r1, #0
40702c48:	da00000a 	ble	40702c78 <ddr_dataeye_deskew+0x1ac>
40702c4c:	e2411001 	sub	r1, r1, #1
40702c50:	e1a00004 	mov	r0, r4
40702c54:	e58d1020 	str	r1, [sp, #32]
40702c58:	ebfffe05 	bl	40702474 <ddr_phy_set_dq_bdl>
40702c5c:	e1a00004 	mov	r0, r4
40702c60:	ebffff41 	bl	4070296c <ddr_dataeye_check_dq>
40702c64:	e3500000 	cmp	r0, #0
40702c68:	0afffff4 	beq	40702c40 <ddr_dataeye_deskew+0x174>
40702c6c:	e59d3020 	ldr	r3, [sp, #32]
40702c70:	e2833001 	add	r3, r3, #1
40702c74:	e58d3020 	str	r3, [sp, #32]
40702c78:	e59d001c 	ldr	r0, [sp, #28]
40702c7c:	e28d2028 	add	r2, sp, #40	; 0x28
40702c80:	e3a03004 	mov	r3, #4
40702c84:	e3a0107f 	mov	r1, #127	; 0x7f
40702c88:	e5220004 	str	r0, [r2, #-4]!
40702c8c:	e58d4000 	str	r4, [sp]
40702c90:	ebffff56 	bl	407029f0 <ddr_dataeye_search_dq>
40702c94:	e59d1024 	ldr	r1, [sp, #36]	; 0x24
40702c98:	e351007e 	cmp	r1, #126	; 0x7e
40702c9c:	ca00000a 	bgt	40702ccc <ddr_dataeye_deskew+0x200>
40702ca0:	e2811001 	add	r1, r1, #1
40702ca4:	e1a00004 	mov	r0, r4
40702ca8:	e58d1024 	str	r1, [sp, #36]	; 0x24
40702cac:	ebfffdf0 	bl	40702474 <ddr_phy_set_dq_bdl>
40702cb0:	e1a00004 	mov	r0, r4
40702cb4:	ebffff2c 	bl	4070296c <ddr_dataeye_check_dq>
40702cb8:	e3500000 	cmp	r0, #0
40702cbc:	0afffff4 	beq	40702c94 <ddr_dataeye_deskew+0x1c8>
40702cc0:	e59d3024 	ldr	r3, [sp, #36]	; 0x24
40702cc4:	e2433001 	sub	r3, r3, #1
40702cc8:	e58d3024 	str	r3, [sp, #36]	; 0x24
40702ccc:	e1a0100b 	mov	r1, fp
40702cd0:	e1a00004 	mov	r0, r4
40702cd4:	ebfffde6 	bl	40702474 <ddr_phy_set_dq_bdl>
40702cd8:	e59d3020 	ldr	r3, [sp, #32]
40702cdc:	e59d1024 	ldr	r1, [sp, #36]	; 0x24
40702ce0:	e0860107 	add	r0, r6, r7, lsl #2
40702ce4:	e0412003 	sub	r2, r1, r3
40702ce8:	e1811803 	orr	r1, r1, r3, lsl #16
40702cec:	e2822001 	add	r2, r2, #1
40702cf0:	e7861107 	str	r1, [r6, r7, lsl #2]
40702cf4:	e08330a2 	add	r3, r3, r2, lsr #1
40702cf8:	e1833802 	orr	r3, r3, r2, lsl #16
40702cfc:	e5803080 	str	r3, [r0, #128]	; 0x80
40702d00:	eaffffa1 	b	40702b8c <ddr_dataeye_deskew+0xc0>
40702d04:	e6ff7077 	uxth	r7, r7
40702d08:	e1a00004 	mov	r0, r4
40702d0c:	e0888007 	add	r8, r8, r7
40702d10:	e3a0a000 	mov	sl, #0
40702d14:	e1a01007 	mov	r1, r7
40702d18:	ebfffdd5 	bl	40702474 <ddr_phy_set_dq_bdl>
40702d1c:	e5963100 	ldr	r3, [r6, #256]	; 0x100
40702d20:	e083b00b 	add	fp, r3, fp
40702d24:	e586b100 	str	fp, [r6, #256]	; 0x100
40702d28:	eaffffab 	b	40702bdc <ddr_dataeye_deskew+0x110>

40702d2c <ddr_vref_get_win>:
40702d2c:	e92d4070 	push	{r4, r5, r6, lr}
40702d30:	e3a03000 	mov	r3, #0
40702d34:	e5813100 	str	r3, [r1, #256]	; 0x100
40702d38:	e1a05001 	mov	r5, r1
40702d3c:	e5903050 	ldr	r3, [r0, #80]	; 0x50
40702d40:	e1a04000 	mov	r4, r0
40702d44:	e3530001 	cmp	r3, #1
40702d48:	13a01032 	movne	r1, #50	; 0x32
40702d4c:	1a000003 	bne	40702d60 <ddr_vref_get_win+0x34>
40702d50:	e5903060 	ldr	r3, [r0, #96]	; 0x60
40702d54:	e3530000 	cmp	r3, #0
40702d58:	03a0101f 	moveq	r1, #31
40702d5c:	13a0100f 	movne	r1, #15
40702d60:	e1520001 	cmp	r2, r1
40702d64:	e1a00004 	mov	r0, r4
40702d68:	31a01002 	movcc	r1, r2
40702d6c:	ebfffc66 	bl	40701f0c <ddr_vref_set>
40702d70:	e1a01005 	mov	r1, r5
40702d74:	e1a00004 	mov	r0, r4
40702d78:	ebffff53 	bl	40702acc <ddr_dataeye_deskew>
40702d7c:	e5950100 	ldr	r0, [r5, #256]	; 0x100
40702d80:	e8bd8070 	pop	{r4, r5, r6, pc}

40702d84 <ddr_vref_find_best>:
40702d84:	e92d4df3 	push	{r0, r1, r4, r5, r6, r7, r8, sl, fp, lr}
40702d88:	e1a0b003 	mov	fp, r3
40702d8c:	e5903050 	ldr	r3, [r0, #80]	; 0x50
40702d90:	e1a08000 	mov	r8, r0
40702d94:	e1a0a001 	mov	sl, r1
40702d98:	e3530001 	cmp	r3, #1
40702d9c:	13a07032 	movne	r7, #50	; 0x32
40702da0:	1a000003 	bne	40702db4 <ddr_vref_find_best+0x30>
40702da4:	e5903060 	ldr	r3, [r0, #96]	; 0x60
40702da8:	e3530000 	cmp	r3, #0
40702dac:	03a0701f 	moveq	r7, #31
40702db0:	13a0700f 	movne	r7, #15
40702db4:	e1570002 	cmp	r7, r2
40702db8:	e3a06000 	mov	r6, #0
40702dbc:	e08b5002 	add	r5, fp, r2
40702dc0:	e1a03006 	mov	r3, r6
40702dc4:	31a04007 	movcc	r4, r7
40702dc8:	21a04002 	movcs	r4, r2
40702dcc:	e1570005 	cmp	r7, r5
40702dd0:	3a00000a 	bcc	40702e00 <ddr_vref_find_best+0x7c>
40702dd4:	e1a02005 	mov	r2, r5
40702dd8:	e1a0100a 	mov	r1, sl
40702ddc:	e1a00008 	mov	r0, r8
40702de0:	e58d3004 	str	r3, [sp, #4]
40702de4:	ebffffd0 	bl	40702d2c <ddr_vref_get_win>
40702de8:	e59d3004 	ldr	r3, [sp, #4]
40702dec:	e1530000 	cmp	r3, r0
40702df0:	9a000005 	bls	40702e0c <ddr_vref_find_best+0x88>
40702df4:	e2866001 	add	r6, r6, #1
40702df8:	e3560003 	cmp	r6, #3
40702dfc:	1a000005 	bne	40702e18 <ddr_vref_find_best+0x94>
40702e00:	e1a00004 	mov	r0, r4
40702e04:	e28dd008 	add	sp, sp, #8
40702e08:	e8bd8df0 	pop	{r4, r5, r6, r7, r8, sl, fp, pc}
40702e0c:	e1a03000 	mov	r3, r0
40702e10:	e1a04005 	mov	r4, r5
40702e14:	e3a06000 	mov	r6, #0
40702e18:	e085500b 	add	r5, r5, fp
40702e1c:	eaffffea 	b	40702dcc <ddr_vref_find_best+0x48>

40702e20 <ddr_vref_cal>:
40702e20:	e92d41f0 	push	{r4, r5, r6, r7, r8, lr}
40702e24:	e1a06001 	mov	r6, r1
40702e28:	e5903050 	ldr	r3, [r0, #80]	; 0x50
40702e2c:	e1a04000 	mov	r4, r0
40702e30:	e5902054 	ldr	r2, [r0, #84]	; 0x54
40702e34:	e3530001 	cmp	r3, #1
40702e38:	e5903040 	ldr	r3, [r0, #64]	; 0x40
40702e3c:	05901060 	ldreq	r1, [r0, #96]	; 0x60
40702e40:	02833f9d 	addeq	r3, r3, #628	; 0x274
40702e44:	12833e27 	addne	r3, r3, #624	; 0x270
40702e48:	00833501 	addeq	r3, r3, r1, lsl #10
40702e4c:	17935382 	ldrne	r5, [r3, r2, lsl #7]
40702e50:	e1a01006 	mov	r1, r6
40702e54:	07935382 	ldreq	r5, [r3, r2, lsl #7]
40702e58:	1205503f 	andne	r5, r5, #63	; 0x3f
40702e5c:	0205501f 	andeq	r5, r5, #31
40702e60:	e2452003 	sub	r2, r5, #3
40702e64:	ebffffb0 	bl	40702d2c <ddr_vref_get_win>
40702e68:	e2852003 	add	r2, r5, #3
40702e6c:	e1a01006 	mov	r1, r6
40702e70:	e1a07000 	mov	r7, r0
40702e74:	e1a00004 	mov	r0, r4
40702e78:	ebffffab 	bl	40702d2c <ddr_vref_get_win>
40702e7c:	e1570000 	cmp	r7, r0
40702e80:	2a000008 	bcs	40702ea8 <ddr_vref_cal+0x88>
40702e84:	e3a03001 	mov	r3, #1
40702e88:	e1a01006 	mov	r1, r6
40702e8c:	e1a02005 	mov	r2, r5
40702e90:	e1a00004 	mov	r0, r4
40702e94:	ebffffba 	bl	40702d84 <ddr_vref_find_best>
40702e98:	e1a01000 	mov	r1, r0
40702e9c:	e1a00004 	mov	r0, r4
40702ea0:	e8bd41f0 	pop	{r4, r5, r6, r7, r8, lr}
40702ea4:	eafffc18 	b	40701f0c <ddr_vref_set>
40702ea8:	9a000001 	bls	40702eb4 <ddr_vref_cal+0x94>
40702eac:	e3e03000 	mvn	r3, #0
40702eb0:	eafffff4 	b	40702e88 <ddr_vref_cal+0x68>
40702eb4:	e5943050 	ldr	r3, [r4, #80]	; 0x50
40702eb8:	e3530001 	cmp	r3, #1
40702ebc:	13a03032 	movne	r3, #50	; 0x32
40702ec0:	1a000003 	bne	40702ed4 <ddr_vref_cal+0xb4>
40702ec4:	e5943060 	ldr	r3, [r4, #96]	; 0x60
40702ec8:	e3530000 	cmp	r3, #0
40702ecc:	03a0301f 	moveq	r3, #31
40702ed0:	13a0300f 	movne	r3, #15
40702ed4:	e15500a3 	cmp	r5, r3, lsr #1
40702ed8:	2afffff3 	bcs	40702eac <ddr_vref_cal+0x8c>
40702edc:	eaffffe8 	b	40702e84 <ddr_vref_cal+0x64>

40702ee0 <ddr_adjust_move_win.constprop.14>:
40702ee0:	e92d4df3 	push	{r0, r1, r4, r5, r6, r7, r8, sl, fp, lr}
40702ee4:	e1a0b001 	mov	fp, r1
40702ee8:	e5901050 	ldr	r1, [r0, #80]	; 0x50
40702eec:	e1a0a002 	mov	sl, r2
40702ef0:	e1a04000 	mov	r4, r0
40702ef4:	e5902054 	ldr	r2, [r0, #84]	; 0x54
40702ef8:	e3510002 	cmp	r1, #2
40702efc:	e5903040 	ldr	r3, [r0, #64]	; 0x40
40702f00:	0a000024 	beq	40702f98 <ddr_adjust_move_win.constprop.14+0xb8>
40702f04:	e3510001 	cmp	r1, #1
40702f08:	130081ff 	movwne	r8, #511	; 0x1ff
40702f0c:	1a000022 	bne	40702f9c <ddr_adjust_move_win.constprop.14+0xbc>
40702f10:	e2833f8b 	add	r3, r3, #556	; 0x22c
40702f14:	e30081ff 	movw	r8, #511	; 0x1ff
40702f18:	e7936382 	ldr	r6, [r3, r2, lsl #7]
40702f1c:	e7e86056 	ubfx	r6, r6, #0, #9
40702f20:	e1a05006 	mov	r5, r6
40702f24:	e3a07000 	mov	r7, #0
40702f28:	e1580007 	cmp	r8, r7
40702f2c:	3a000017 	bcc	40702f90 <ddr_adjust_move_win.constprop.14+0xb0>
40702f30:	e5943050 	ldr	r3, [r4, #80]	; 0x50
40702f34:	e3530002 	cmp	r3, #2
40702f38:	1a00001d 	bne	40702fb4 <ddr_adjust_move_win.constprop.14+0xd4>
40702f3c:	e1a00004 	mov	r0, r4
40702f40:	e58d3004 	str	r3, [sp, #4]
40702f44:	ebfffb3f 	bl	40701c48 <ddr_adjust_get_average>
40702f48:	e59d3004 	ldr	r3, [sp, #4]
40702f4c:	e3500037 	cmp	r0, #55	; 0x37
40702f50:	9a000002 	bls	40702f60 <ddr_adjust_move_win.constprop.14+0x80>
40702f54:	e3500048 	cmp	r0, #72	; 0x48
40702f58:	83a03004 	movhi	r3, #4
40702f5c:	93a03001 	movls	r3, #1
40702f60:	e3a02001 	mov	r2, #1
40702f64:	e153000a 	cmp	r3, sl
40702f68:	13530001 	cmpne	r3, #1
40702f6c:	0a000007 	beq	40702f90 <ddr_adjust_move_win.constprop.14+0xb0>
40702f70:	e5943050 	ldr	r3, [r4, #80]	; 0x50
40702f74:	e3530001 	cmp	r3, #1
40702f78:	1a00001c 	bne	40702ff0 <ddr_adjust_move_win.constprop.14+0x110>
40702f7c:	e35a0004 	cmp	sl, #4
40702f80:	00855002 	addeq	r5, r5, r2
40702f84:	10455002 	subne	r5, r5, r2
40702f88:	e3550c02 	cmp	r5, #512	; 0x200
40702f8c:	3a00001c 	bcc	40703004 <ddr_adjust_move_win.constprop.14+0x124>
40702f90:	e28dd008 	add	sp, sp, #8
40702f94:	e8bd8df0 	pop	{r4, r5, r6, r7, r8, sl, fp, pc}
40702f98:	e3a0801f 	mov	r8, #31
40702f9c:	e5941060 	ldr	r1, [r4, #96]	; 0x60
40702fa0:	e2833f8d 	add	r3, r3, #564	; 0x234
40702fa4:	e0833501 	add	r3, r3, r1, lsl #10
40702fa8:	e7936382 	ldr	r6, [r3, r2, lsl #7]
40702fac:	e7e46456 	ubfx	r6, r6, #8, #5
40702fb0:	eaffffda 	b	40702f20 <ddr_adjust_move_win.constprop.14+0x40>
40702fb4:	e1a00004 	mov	r0, r4
40702fb8:	ebfffb22 	bl	40701c48 <ddr_adjust_get_average>
40702fbc:	e3500040 	cmp	r0, #64	; 0x40
40702fc0:	9a000004 	bls	40702fd8 <ddr_adjust_move_win.constprop.14+0xf8>
40702fc4:	e3500048 	cmp	r0, #72	; 0x48
40702fc8:	e2402040 	sub	r2, r0, #64	; 0x40
40702fcc:	83a03004 	movhi	r3, #4
40702fd0:	93a03001 	movls	r3, #1
40702fd4:	eaffffe2 	b	40702f64 <ddr_adjust_move_win.constprop.14+0x84>
40702fd8:	12602040 	rsbne	r2, r0, #64	; 0x40
40702fdc:	03a02001 	moveq	r2, #1
40702fe0:	e3500037 	cmp	r0, #55	; 0x37
40702fe4:	83a03001 	movhi	r3, #1
40702fe8:	93a03002 	movls	r3, #2
40702fec:	eaffffdc 	b	40702f64 <ddr_adjust_move_win.constprop.14+0x84>
40702ff0:	e35a0004 	cmp	sl, #4
40702ff4:	00455002 	subeq	r5, r5, r2
40702ff8:	10855002 	addne	r5, r5, r2
40702ffc:	e355001f 	cmp	r5, #31
40703000:	8affffe2 	bhi	40702f90 <ddr_adjust_move_win.constprop.14+0xb0>
40703004:	e1a01005 	mov	r1, r5
40703008:	e1a00004 	mov	r0, r4
4070300c:	ebfffd6a 	bl	407025bc <ddr_adjust_set_val>
40703010:	e1a0100b 	mov	r1, fp
40703014:	e1a00004 	mov	r0, r4
40703018:	ebfffeab 	bl	40702acc <ddr_dataeye_deskew>
4070301c:	e3500000 	cmp	r0, #0
40703020:	0a000007 	beq	40703044 <ddr_adjust_move_win.constprop.14+0x164>
40703024:	e1a01006 	mov	r1, r6
40703028:	e1a00004 	mov	r0, r4
4070302c:	ebfffd62 	bl	407025bc <ddr_adjust_set_val>
40703030:	e1a0100b 	mov	r1, fp
40703034:	e1a00004 	mov	r0, r4
40703038:	e28dd008 	add	sp, sp, #8
4070303c:	e8bd4df0 	pop	{r4, r5, r6, r7, r8, sl, fp, lr}
40703040:	eafffea1 	b	40702acc <ddr_dataeye_deskew>
40703044:	e2877001 	add	r7, r7, #1
40703048:	eaffffb6 	b	40702f28 <ddr_adjust_move_win.constprop.14+0x48>

4070304c <ddr_adjust_dataeye>:
4070304c:	e92d41f0 	push	{r4, r5, r6, r7, r8, lr}
40703050:	e5905048 	ldr	r5, [r0, #72]	; 0x48
40703054:	e2155201 	ands	r5, r5, #268435456	; 0x10000000
40703058:	0a000014 	beq	407030b0 <ddr_adjust_dataeye+0x64>
4070305c:	e8bd81f0 	pop	{r4, r5, r6, r7, r8, pc}
40703060:	e0852082 	add	r2, r5, r2, lsl #1
40703064:	e1a00004 	mov	r0, r4
40703068:	e5842054 	str	r2, [r4, #84]	; 0x54
4070306c:	ebfffaf5 	bl	40701c48 <ddr_adjust_get_average>
40703070:	e3500037 	cmp	r0, #55	; 0x37
40703074:	93a02004 	movls	r2, #4
40703078:	9a000014 	bls	407030d0 <ddr_adjust_dataeye+0x84>
4070307c:	e3500048 	cmp	r0, #72	; 0x48
40703080:	83a02002 	movhi	r2, #2
40703084:	8a000011 	bhi	407030d0 <ddr_adjust_dataeye+0x84>
40703088:	e2855001 	add	r5, r5, #1
4070308c:	e594305c 	ldr	r3, [r4, #92]	; 0x5c
40703090:	e5942064 	ldr	r2, [r4, #100]	; 0x64
40703094:	e0030398 	mul	r3, r8, r3
40703098:	e0233297 	mla	r3, r7, r2, r3
4070309c:	e0843003 	add	r3, r4, r3
407030a0:	e5933018 	ldr	r3, [r3, #24]
407030a4:	e1550003 	cmp	r5, r3
407030a8:	3affffec 	bcc	40703060 <ddr_adjust_dataeye+0x14>
407030ac:	e8bd81f0 	pop	{r4, r5, r6, r7, r8, pc}
407030b0:	e5903068 	ldr	r3, [r0, #104]	; 0x68
407030b4:	e3530000 	cmp	r3, #0
407030b8:	08bd81f0 	popeq	{r4, r5, r6, r7, r8, pc}
407030bc:	e1a06001 	mov	r6, r1
407030c0:	e1a04000 	mov	r4, r0
407030c4:	e3a0700c 	mov	r7, #12
407030c8:	e3a0803c 	mov	r8, #60	; 0x3c
407030cc:	eaffffee 	b	4070308c <ddr_adjust_dataeye+0x40>
407030d0:	e1a01006 	mov	r1, r6
407030d4:	e1a00004 	mov	r0, r4
407030d8:	ebffff80 	bl	40702ee0 <ddr_adjust_move_win.constprop.14>
407030dc:	eaffffe9 	b	40703088 <ddr_adjust_dataeye+0x3c>

407030e0 <ddr_dataeye_process>:
407030e0:	e92d4df0 	push	{r4, r5, r6, r7, r8, sl, fp, lr}
407030e4:	e3a06000 	mov	r6, #0
407030e8:	e1a04000 	mov	r4, r0
407030ec:	e1a07001 	mov	r7, r1
407030f0:	e1a05006 	mov	r5, r6
407030f4:	e3a0800c 	mov	r8, #12
407030f8:	e3a0a03c 	mov	sl, #60	; 0x3c
407030fc:	e594305c 	ldr	r3, [r4, #92]	; 0x5c
40703100:	e5942064 	ldr	r2, [r4, #100]	; 0x64
40703104:	e003039a 	mul	r3, sl, r3
40703108:	e0233298 	mla	r3, r8, r2, r3
4070310c:	e0843003 	add	r3, r4, r3
40703110:	e5933018 	ldr	r3, [r3, #24]
40703114:	e1530006 	cmp	r3, r6
40703118:	8a00000a 	bhi	40703148 <ddr_dataeye_process+0x68>
4070311c:	e3550000 	cmp	r5, #0
40703120:	13e05000 	mvnne	r5, #0
40703124:	1a000002 	bne	40703134 <ddr_dataeye_process+0x54>
40703128:	e1a01007 	mov	r1, r7
4070312c:	e1a00004 	mov	r0, r4
40703130:	ebffffc5 	bl	4070304c <ddr_adjust_dataeye>
40703134:	e1a00004 	mov	r0, r4
40703138:	e1a01007 	mov	r1, r7
4070313c:	eb000360 	bl	40703ec4 <ddr_result_data_save>
40703140:	e1a00005 	mov	r0, r5
40703144:	e8bd8df0 	pop	{r4, r5, r6, r7, r8, sl, fp, pc}
40703148:	e0862082 	add	r2, r6, r2, lsl #1
4070314c:	e1a01007 	mov	r1, r7
40703150:	e5842054 	str	r2, [r4, #84]	; 0x54
40703154:	e1a00004 	mov	r0, r4
40703158:	ebfffe5b 	bl	40702acc <ddr_dataeye_deskew>
4070315c:	e2866001 	add	r6, r6, #1
40703160:	e0855000 	add	r5, r5, r0
40703164:	eaffffe4 	b	407030fc <ddr_dataeye_process+0x1c>

40703168 <ddr_dataeye_training>:
40703168:	e92d4030 	push	{r4, r5, lr}
4070316c:	e24ddf43 	sub	sp, sp, #268	; 0x10c
40703170:	e1a04000 	mov	r4, r0
40703174:	e3a03002 	mov	r3, #2
40703178:	e3a02f41 	mov	r2, #260	; 0x104
4070317c:	e5803050 	str	r3, [r0, #80]	; 0x50
40703180:	e3a01000 	mov	r1, #0
40703184:	e28d0004 	add	r0, sp, #4
40703188:	ebfffadb 	bl	40701cfc <ddrtr_memset>
4070318c:	e28d1004 	add	r1, sp, #4
40703190:	e1a00004 	mov	r0, r4
40703194:	ebffffd1 	bl	407030e0 <ddr_dataeye_process>
40703198:	e3a03001 	mov	r3, #1
4070319c:	e3a02f41 	mov	r2, #260	; 0x104
407031a0:	e5843050 	str	r3, [r4, #80]	; 0x50
407031a4:	e3a01000 	mov	r1, #0
407031a8:	e1a05000 	mov	r5, r0
407031ac:	e28d0004 	add	r0, sp, #4
407031b0:	ebfffad1 	bl	40701cfc <ddrtr_memset>
407031b4:	e28d1004 	add	r1, sp, #4
407031b8:	e1a00004 	mov	r0, r4
407031bc:	ebffffc7 	bl	407030e0 <ddr_dataeye_process>
407031c0:	e1953000 	orrs	r3, r5, r0
407031c4:	13e00000 	mvnne	r0, #0
407031c8:	03a00000 	moveq	r0, #0
407031cc:	e28ddf43 	add	sp, sp, #268	; 0x10c
407031d0:	e8bd8030 	pop	{r4, r5, pc}

407031d4 <ddr_dataeye_training_func>:
407031d4:	e92d4030 	push	{r4, r5, lr}
407031d8:	e24dd03c 	sub	sp, sp, #60	; 0x3c
407031dc:	e5903048 	ldr	r3, [r0, #72]	; 0x48
407031e0:	e3130801 	tst	r3, #65536	; 0x10000
407031e4:	13a05000 	movne	r5, #0
407031e8:	1a000011 	bne	40703234 <ddr_dataeye_training_func+0x60>
407031ec:	e1a04000 	mov	r4, r0
407031f0:	e3a02801 	mov	r2, #65536	; 0x10000
407031f4:	e1a0100d 	mov	r1, sp
407031f8:	ebfffc40 	bl	40702300 <ddr_training_save_reg>
407031fc:	e1a00004 	mov	r0, r4
40703200:	ebfffc18 	bl	40702268 <ddr_training_switch_axi>
40703204:	e3a01002 	mov	r1, #2
40703208:	e1a00004 	mov	r0, r4
4070320c:	ebfffd4d 	bl	40702748 <ddr_ddrt_init>
40703210:	e3a03001 	mov	r3, #1
40703214:	e1a00004 	mov	r0, r4
40703218:	e5843068 	str	r3, [r4, #104]	; 0x68
4070321c:	e584306c 	str	r3, [r4, #108]	; 0x6c
40703220:	ebffffd0 	bl	40703168 <ddr_dataeye_training>
40703224:	e1a0100d 	mov	r1, sp
40703228:	e1a05000 	mov	r5, r0
4070322c:	e1a00004 	mov	r0, r4
40703230:	ebfffc6f 	bl	407023f4 <ddr_training_restore_reg>
40703234:	e1a00005 	mov	r0, r5
40703238:	e28dd03c 	add	sp, sp, #60	; 0x3c
4070323c:	e8bd8030 	pop	{r4, r5, pc}

40703240 <ddr_hw_dataeye_read>:
40703240:	e92d4070 	push	{r4, r5, r6, lr}
40703244:	e3a0203c 	mov	r2, #60	; 0x3c
40703248:	e590305c 	ldr	r3, [r0, #92]	; 0x5c
4070324c:	e1a04000 	mov	r4, r0
40703250:	e5905040 	ldr	r5, [r0, #64]	; 0x40
40703254:	e0230392 	mla	r3, r2, r3, r0
40703258:	e5936010 	ldr	r6, [r3, #16]
4070325c:	ebfffd2d 	bl	40702718 <ddr_training_cfg_init>
40703260:	e3a03000 	mov	r3, #0
40703264:	e2850f8b 	add	r0, r5, #556	; 0x22c
40703268:	e285cf87 	add	ip, r5, #540	; 0x21c
4070326c:	e285ee22 	add	lr, r5, #544	; 0x220
40703270:	e1a02003 	mov	r2, r3
40703274:	e1530006 	cmp	r3, r6
40703278:	1a000005 	bne	40703294 <ddr_hw_dataeye_read+0x54>
4070327c:	e1a00005 	mov	r0, r5
40703280:	ebfffc12 	bl	407022d0 <ddr_phy_cfg_update>
40703284:	e1a00004 	mov	r0, r4
40703288:	e3a01c01 	mov	r1, #256	; 0x100
4070328c:	e8bd4070 	pop	{r4, r5, r6, lr}
40703290:	eafffba5 	b	4070212c <ddr_hw_training_process>
40703294:	e5941060 	ldr	r1, [r4, #96]	; 0x60
40703298:	e08c1501 	add	r1, ip, r1, lsl #10
4070329c:	e7812383 	str	r2, [r1, r3, lsl #7]
407032a0:	e5941060 	ldr	r1, [r4, #96]	; 0x60
407032a4:	e08e1501 	add	r1, lr, r1, lsl #10
407032a8:	e7812383 	str	r2, [r1, r3, lsl #7]
407032ac:	e2833001 	add	r3, r3, #1
407032b0:	e4802080 	str	r2, [r0], #128	; 0x80
407032b4:	eaffffee 	b	40703274 <ddr_hw_dataeye_read+0x34>

407032b8 <ddr_hw_training_ctl>:
407032b8:	e92d4df0 	push	{r4, r5, r6, r7, r8, sl, fp, lr}
407032bc:	e28db01c 	add	fp, sp, #28
407032c0:	e24dd040 	sub	sp, sp, #64	; 0x40
407032c4:	e5905040 	ldr	r5, [r0, #64]	; 0x40
407032c8:	e5907074 	ldr	r7, [r0, #116]	; 0x74
407032cc:	e5906048 	ldr	r6, [r0, #72]	; 0x48
407032d0:	e59530c4 	ldr	r3, [r5, #196]	; 0xc4
407032d4:	e3570000 	cmp	r7, #0
407032d8:	13560000 	cmpne	r6, #0
407032dc:	e50b3020 	str	r3, [fp, #-32]	; 0xffffffe0
407032e0:	03a07000 	moveq	r7, #0
407032e4:	0a00005e 	beq	40703464 <ddr_hw_training_ctl+0x1ac>
407032e8:	e590305c 	ldr	r3, [r0, #92]	; 0x5c
407032ec:	e3a0803c 	mov	r8, #60	; 0x3c
407032f0:	e1a04000 	mov	r4, r0
407032f4:	e0230398 	mla	r3, r8, r3, r0
407032f8:	e1a00005 	mov	r0, r5
407032fc:	e5933010 	ldr	r3, [r3, #16]
40703300:	e50b3040 	str	r3, [fp, #-64]	; 0xffffffc0
40703304:	ebfffbf1 	bl	407022d0 <ddr_phy_cfg_update>
40703308:	e2061902 	and	r1, r6, #32768	; 0x8000
4070330c:	e1a00004 	mov	r0, r4
40703310:	ebfffb85 	bl	4070212c <ddr_hw_training_process>
40703314:	e206100e 	and	r1, r6, #14
40703318:	e1a0a000 	mov	sl, r0
4070331c:	e1a00004 	mov	r0, r4
40703320:	ebfffb81 	bl	4070212c <ddr_hw_training_process>
40703324:	e5943060 	ldr	r3, [r4, #96]	; 0x60
40703328:	e3530000 	cmp	r3, #0
4070332c:	e08aa000 	add	sl, sl, r0
40703330:	0a00004e 	beq	40703470 <ddr_hw_training_ctl+0x1b8>
40703334:	e3a0e000 	mov	lr, #0
40703338:	e51b3040 	ldr	r3, [fp, #-64]	; 0xffffffc0
4070333c:	e15e0003 	cmp	lr, r3
40703340:	1a000055 	bne	4070349c <ddr_hw_training_ctl+0x1e4>
40703344:	e594305c 	ldr	r3, [r4, #92]	; 0x5c
40703348:	e3a0203c 	mov	r2, #60	; 0x3c
4070334c:	e2061b05 	and	r1, r6, #5120	; 0x1400
40703350:	e0234392 	mla	r3, r2, r3, r4
40703354:	e5933004 	ldr	r3, [r3, #4]
40703358:	e3530006 	cmp	r3, #6
4070335c:	1a0000af 	bne	40703620 <ddr_hw_training_ctl+0x368>
40703360:	e5958064 	ldr	r8, [r5, #100]	; 0x64
40703364:	e1a00004 	mov	r0, r4
40703368:	e3c8320f 	bic	r3, r8, #-268435456	; 0xf0000000
4070336c:	e5853064 	str	r3, [r5, #100]	; 0x64
40703370:	ebfffb6d 	bl	4070212c <ddr_hw_training_process>
40703374:	e5858064 	str	r8, [r5, #100]	; 0x64
40703378:	e5958048 	ldr	r8, [r5, #72]	; 0x48
4070337c:	e3c83001 	bic	r3, r8, #1
40703380:	e5853048 	str	r3, [r5, #72]	; 0x48
40703384:	e08a7000 	add	r7, sl, r0
40703388:	e206a602 	and	sl, r6, #2097152	; 0x200000
4070338c:	e1a00004 	mov	r0, r4
40703390:	e1a0100a 	mov	r1, sl
40703394:	ebfffb64 	bl	4070212c <ddr_hw_training_process>
40703398:	e3883001 	orr	r3, r8, #1
4070339c:	e1a0100a 	mov	r1, sl
407033a0:	e5853048 	str	r3, [r5, #72]	; 0x48
407033a4:	e0877000 	add	r7, r7, r0
407033a8:	e1a00004 	mov	r0, r4
407033ac:	ebfffb5e 	bl	4070212c <ddr_hw_training_process>
407033b0:	e5858048 	str	r8, [r5, #72]	; 0x48
407033b4:	e2061b01 	and	r1, r6, #1024	; 0x400
407033b8:	e0877000 	add	r7, r7, r0
407033bc:	e1a00004 	mov	r0, r4
407033c0:	ebfffb59 	bl	4070212c <ddr_hw_training_process>
407033c4:	e0877000 	add	r7, r7, r0
407033c8:	e2061b02 	and	r1, r6, #2048	; 0x800
407033cc:	e1a00004 	mov	r0, r4
407033d0:	ebfffb55 	bl	4070212c <ddr_hw_training_process>
407033d4:	e2061501 	and	r1, r6, #4194304	; 0x400000
407033d8:	e2068701 	and	r8, r6, #262144	; 0x40000
407033dc:	e0877000 	add	r7, r7, r0
407033e0:	e1a00004 	mov	r0, r4
407033e4:	ebfffb50 	bl	4070212c <ddr_hw_training_process>
407033e8:	e51b3020 	ldr	r3, [fp, #-32]	; 0xffffffe0
407033ec:	e1a01008 	mov	r1, r8
407033f0:	e3c33102 	bic	r3, r3, #-2147483648	; 0x80000000
407033f4:	e58530c4 	str	r3, [r5, #196]	; 0xc4
407033f8:	e59530c0 	ldr	r3, [r5, #192]	; 0xc0
407033fc:	e3833102 	orr	r3, r3, #-2147483648	; 0x80000000
40703400:	e58530c0 	str	r3, [r5, #192]	; 0xc0
40703404:	e0877000 	add	r7, r7, r0
40703408:	e1a00004 	mov	r0, r4
4070340c:	ebfffb46 	bl	4070212c <ddr_hw_training_process>
40703410:	e1a01008 	mov	r1, r8
40703414:	e0877000 	add	r7, r7, r0
40703418:	e1a00004 	mov	r0, r4
4070341c:	ebfffb42 	bl	4070212c <ddr_hw_training_process>
40703420:	e59530c0 	ldr	r3, [r5, #192]	; 0xc0
40703424:	e1a01008 	mov	r1, r8
40703428:	e3c33102 	bic	r3, r3, #-2147483648	; 0x80000000
4070342c:	e58530c0 	str	r3, [r5, #192]	; 0xc0
40703430:	e0877000 	add	r7, r7, r0
40703434:	e1a00004 	mov	r0, r4
40703438:	ebfffb3b 	bl	4070212c <ddr_hw_training_process>
4070343c:	e51b3020 	ldr	r3, [fp, #-32]	; 0xffffffe0
40703440:	e59f11e8 	ldr	r1, [pc, #488]	; 40703630 <ddr_hw_training_ctl+0x378>
40703444:	e58530c4 	str	r3, [r5, #196]	; 0xc4
40703448:	e0011006 	and	r1, r1, r6
4070344c:	e0877000 	add	r7, r7, r0
40703450:	e1a00004 	mov	r0, r4
40703454:	ebfffb34 	bl	4070212c <ddr_hw_training_process>
40703458:	e0877000 	add	r7, r7, r0
4070345c:	e1a00005 	mov	r0, r5
40703460:	ebfffb9a 	bl	407022d0 <ddr_phy_cfg_update>
40703464:	e1a00007 	mov	r0, r7
40703468:	e24bd01c 	sub	sp, fp, #28
4070346c:	e8bd8df0 	pop	{r4, r5, r6, r7, r8, sl, fp, pc}
40703470:	e594205c 	ldr	r2, [r4, #92]	; 0x5c
40703474:	e0284298 	mla	r8, r8, r2, r4
40703478:	e5942040 	ldr	r2, [r4, #64]	; 0x40
4070347c:	e2822f8b 	add	r2, r2, #556	; 0x22c
40703480:	e5981010 	ldr	r1, [r8, #16]
40703484:	e1510003 	cmp	r1, r3
40703488:	0affffa9 	beq	40703334 <ddr_hw_training_ctl+0x7c>
4070348c:	e4920080 	ldr	r0, [r2], #128	; 0x80
40703490:	e7870103 	str	r0, [r7, r3, lsl #2]
40703494:	e2833001 	add	r3, r3, #1
40703498:	eafffff9 	b	40703484 <ddr_hw_training_ctl+0x1cc>
4070349c:	e5941060 	ldr	r1, [r4, #96]	; 0x60
407034a0:	e1a0238e 	lsl	r2, lr, #7
407034a4:	e594c040 	ldr	ip, [r4, #64]	; 0x40
407034a8:	e584e054 	str	lr, [r4, #84]	; 0x54
407034ac:	e08c1501 	add	r1, ip, r1, lsl #10
407034b0:	e28ccf8b 	add	ip, ip, #556	; 0x22c
407034b4:	e0811002 	add	r1, r1, r2
407034b8:	e50b2054 	str	r2, [fp, #-84]	; 0xffffffac
407034bc:	e50bc03c 	str	ip, [fp, #-60]	; 0xffffffc4
407034c0:	e591021c 	ldr	r0, [r1, #540]	; 0x21c
407034c4:	e5912220 	ldr	r2, [r1, #544]	; 0x220
407034c8:	e5917224 	ldr	r7, [r1, #548]	; 0x224
407034cc:	e79cc38e 	ldr	ip, [ip, lr, lsl #7]
407034d0:	e50bd044 	str	sp, [fp, #-68]	; 0xffffffbc
407034d4:	e24dd030 	sub	sp, sp, #48	; 0x30
407034d8:	e50b7024 	str	r7, [fp, #-36]	; 0xffffffdc
407034dc:	e7e67450 	ubfx	r7, r0, #8, #7
407034e0:	e50bc028 	str	ip, [fp, #-40]	; 0xffffffd8
407034e4:	e200c07f 	and	ip, r0, #127	; 0x7f
407034e8:	e50bc048 	str	ip, [fp, #-72]	; 0xffffffb8
407034ec:	e24d8004 	sub	r8, sp, #4
407034f0:	e58dc000 	str	ip, [sp]
407034f4:	e7e6c850 	ubfx	ip, r0, #16, #7
407034f8:	e7e60c50 	ubfx	r0, r0, #24, #7
407034fc:	e50b002c 	str	r0, [fp, #-44]	; 0xffffffd4
40703500:	e58d000c 	str	r0, [sp, #12]
40703504:	e202007f 	and	r0, r2, #127	; 0x7f
40703508:	e50b004c 	str	r0, [fp, #-76]	; 0xffffffb4
4070350c:	e28d3024 	add	r3, sp, #36	; 0x24
40703510:	e58d0010 	str	r0, [sp, #16]
40703514:	e7e60452 	ubfx	r0, r2, #8, #7
40703518:	e50b0050 	str	r0, [fp, #-80]	; 0xffffffb0
4070351c:	e58d0014 	str	r0, [sp, #20]
40703520:	e7e60852 	ubfx	r0, r2, #16, #7
40703524:	e7e62c52 	ubfx	r2, r2, #24, #7
40703528:	e50b2030 	str	r2, [fp, #-48]	; 0xffffffd0
4070352c:	e58d201c 	str	r2, [sp, #28]
40703530:	e51b2024 	ldr	r2, [fp, #-36]	; 0xffffffdc
40703534:	e58d7004 	str	r7, [sp, #4]
40703538:	e202207f 	and	r2, r2, #127	; 0x7f
4070353c:	e50b2034 	str	r2, [fp, #-52]	; 0xffffffcc
40703540:	e58d2020 	str	r2, [sp, #32]
40703544:	e51b2028 	ldr	r2, [fp, #-40]	; 0xffffffd8
40703548:	e58dc008 	str	ip, [sp, #8]
4070354c:	e7e82052 	ubfx	r2, r2, #0, #9
40703550:	e50b2038 	str	r2, [fp, #-56]	; 0xffffffc8
40703554:	e58d2024 	str	r2, [sp, #36]	; 0x24
40703558:	e3e02000 	mvn	r2, #0
4070355c:	e58d0018 	str	r0, [sp, #24]
40703560:	e50b3058 	str	r3, [fp, #-88]	; 0xffffffa8
40703564:	e5b83004 	ldr	r3, [r8, #4]!
40703568:	e1520003 	cmp	r2, r3
4070356c:	21a02003 	movcs	r2, r3
40703570:	e51b3058 	ldr	r3, [fp, #-88]	; 0xffffffa8
40703574:	e1530008 	cmp	r3, r8
40703578:	1afffff9 	bne	40703564 <ddr_hw_training_ctl+0x2ac>
4070357c:	e04cc002 	sub	ip, ip, r2
40703580:	e51b3048 	ldr	r3, [fp, #-72]	; 0xffffffb8
40703584:	e0477002 	sub	r7, r7, r2
40703588:	e0400002 	sub	r0, r0, r2
4070358c:	e1a0c80c 	lsl	ip, ip, #16
40703590:	e0433002 	sub	r3, r3, r2
40703594:	e18c7407 	orr	r7, ip, r7, lsl #8
40703598:	e1a00800 	lsl	r0, r0, #16
4070359c:	e1877003 	orr	r7, r7, r3
407035a0:	e51b302c 	ldr	r3, [fp, #-44]	; 0xffffffd4
407035a4:	e51bc034 	ldr	ip, [fp, #-52]	; 0xffffffcc
407035a8:	e28ee001 	add	lr, lr, #1
407035ac:	e0433002 	sub	r3, r3, r2
407035b0:	e51b8038 	ldr	r8, [fp, #-56]	; 0xffffffc8
407035b4:	e04cc002 	sub	ip, ip, r2
407035b8:	e1877c03 	orr	r7, r7, r3, lsl #24
407035bc:	e51b3050 	ldr	r3, [fp, #-80]	; 0xffffffb0
407035c0:	e581721c 	str	r7, [r1, #540]	; 0x21c
407035c4:	e0433002 	sub	r3, r3, r2
407035c8:	e1800403 	orr	r0, r0, r3, lsl #8
407035cc:	e51b304c 	ldr	r3, [fp, #-76]	; 0xffffffb4
407035d0:	e0433002 	sub	r3, r3, r2
407035d4:	e1800003 	orr	r0, r0, r3
407035d8:	e51b3030 	ldr	r3, [fp, #-48]	; 0xffffffd0
407035dc:	e0433002 	sub	r3, r3, r2
407035e0:	e0482002 	sub	r2, r8, r2
407035e4:	e1800c03 	orr	r0, r0, r3, lsl #24
407035e8:	e51b3024 	ldr	r3, [fp, #-36]	; 0xffffffdc
407035ec:	e5810220 	str	r0, [r1, #544]	; 0x220
407035f0:	e3c3307f 	bic	r3, r3, #127	; 0x7f
407035f4:	e183300c 	orr	r3, r3, ip
407035f8:	e51bc028 	ldr	ip, [fp, #-40]	; 0xffffffd8
407035fc:	e5813224 	str	r3, [r1, #548]	; 0x224
40703600:	e51b303c 	ldr	r3, [fp, #-60]	; 0xffffffc4
40703604:	e3cccf7f 	bic	ip, ip, #508	; 0x1fc
40703608:	e51b1054 	ldr	r1, [fp, #-84]	; 0xffffffac
4070360c:	e3ccc003 	bic	ip, ip, #3
40703610:	e18c2002 	orr	r2, ip, r2
40703614:	e7832001 	str	r2, [r3, r1]
40703618:	e51bd044 	ldr	sp, [fp, #-68]	; 0xffffffbc
4070361c:	eaffff45 	b	40703338 <ddr_hw_training_ctl+0x80>
40703620:	e1a00004 	mov	r0, r4
40703624:	ebfffac0 	bl	4070212c <ddr_hw_training_process>
40703628:	e08a7000 	add	r7, sl, r0
4070362c:	eaffff65 	b	407033c8 <ddr_hw_training_ctl+0x110>
40703630:	100303f0 	.word	0x100303f0

40703634 <ddr_hw_training>:
40703634:	e92d4df0 	push	{r4, r5, r6, r7, r8, sl, fp, lr}
40703638:	e1a04000 	mov	r4, r0
4070363c:	e24dd080 	sub	sp, sp, #128	; 0x80
40703640:	e3a01001 	mov	r1, #1
40703644:	e28d0048 	add	r0, sp, #72	; 0x48
40703648:	e1a06004 	mov	r6, r4
4070364c:	eb000256 	bl	40703fac <ddr_training_save_reg_custom>
40703650:	e3a07000 	mov	r7, #0
40703654:	e58d7004 	str	r7, [sp, #4]
40703658:	e594303c 	ldr	r3, [r4, #60]	; 0x3c
4070365c:	e1530007 	cmp	r3, r7
40703660:	8a000004 	bhi	40703678 <ddr_hw_training+0x44>
40703664:	e28d0048 	add	r0, sp, #72	; 0x48
40703668:	eb000250 	bl	40703fb0 <ddr_training_restore_reg_custom>
4070366c:	e59d0004 	ldr	r0, [sp, #4]
40703670:	e28dd080 	add	sp, sp, #128	; 0x80
40703674:	e8bd8df0 	pop	{r4, r5, r6, r7, r8, sl, fp, pc}
40703678:	e584705c 	str	r7, [r4, #92]	; 0x5c
4070367c:	e3a02000 	mov	r2, #0
40703680:	e5963000 	ldr	r3, [r6]
40703684:	e3a0500c 	mov	r5, #12
40703688:	e28da018 	add	sl, sp, #24
4070368c:	e5843040 	str	r3, [r4, #64]	; 0x40
40703690:	e596800c 	ldr	r8, [r6, #12]
40703694:	e584a074 	str	sl, [r4, #116]	; 0x74
40703698:	e5963008 	ldr	r3, [r6, #8]
4070369c:	e1530002 	cmp	r3, r2
407036a0:	8a000026 	bhi	40703740 <ddr_hw_training+0x10c>
407036a4:	e3a0b03c 	mov	fp, #60	; 0x3c
407036a8:	e3a05000 	mov	r5, #0
407036ac:	e58d5000 	str	r5, [sp]
407036b0:	e1550008 	cmp	r5, r8
407036b4:	e594305c 	ldr	r3, [r4, #92]	; 0x5c
407036b8:	1a00002a 	bne	40703768 <ddr_hw_training+0x134>
407036bc:	e3550002 	cmp	r5, #2
407036c0:	1a000010 	bne	40703708 <ddr_hw_training+0xd4>
407036c4:	e3a0203c 	mov	r2, #60	; 0x3c
407036c8:	e3a05000 	mov	r5, #0
407036cc:	e0234392 	mla	r3, r2, r3, r4
407036d0:	e28d8024 	add	r8, sp, #36	; 0x24
407036d4:	e1a0b005 	mov	fp, r5
407036d8:	e3a0a001 	mov	sl, #1
407036dc:	e5933010 	ldr	r3, [r3, #16]
407036e0:	e58d3008 	str	r3, [sp, #8]
407036e4:	e5943060 	ldr	r3, [r4, #96]	; 0x60
407036e8:	e58d300c 	str	r3, [sp, #12]
407036ec:	e59d3008 	ldr	r3, [sp, #8]
407036f0:	e1530005 	cmp	r3, r5
407036f4:	1a000048 	bne	4070381c <ddr_hw_training+0x1e8>
407036f8:	e59d300c 	ldr	r3, [sp, #12]
407036fc:	e5940040 	ldr	r0, [r4, #64]	; 0x40
40703700:	e5843060 	str	r3, [r4, #96]	; 0x60
40703704:	ebfffaf1 	bl	407022d0 <ddr_phy_cfg_update>
40703708:	e594305c 	ldr	r3, [r4, #92]	; 0x5c
4070370c:	e3a0503c 	mov	r5, #60	; 0x3c
40703710:	e3a02000 	mov	r2, #0
40703714:	e0050395 	mul	r5, r5, r3
40703718:	e0848005 	add	r8, r4, r5
4070371c:	e5983008 	ldr	r3, [r8, #8]
40703720:	e1530002 	cmp	r3, r2
40703724:	8a00004f 	bhi	40703868 <ddr_hw_training+0x234>
40703728:	e89d000c 	ldm	sp, {r2, r3}
4070372c:	e2877001 	add	r7, r7, #1
40703730:	e286603c 	add	r6, r6, #60	; 0x3c
40703734:	e0833002 	add	r3, r3, r2
40703738:	e58d3004 	str	r3, [sp, #4]
4070373c:	eaffffc5 	b	40703658 <ddr_hw_training+0x24>
40703740:	e0236295 	mla	r3, r5, r2, r6
40703744:	e5930014 	ldr	r0, [r3, #20]
40703748:	e28d3010 	add	r3, sp, #16
4070374c:	e5901108 	ldr	r1, [r0, #264]	; 0x108
40703750:	e7831102 	str	r1, [r3, r2, lsl #2]
40703754:	e3c11eff 	bic	r1, r1, #4080	; 0xff0
40703758:	e3c1100f 	bic	r1, r1, #15
4070375c:	ebfff9de 	bl	40701edc <ddr_training_set_timing>
40703760:	e2822001 	add	r2, r2, #1
40703764:	eaffffcb 	b	40703698 <ddr_hw_training+0x64>
40703768:	e002039b 	mul	r2, fp, r3
4070376c:	e2851005 	add	r1, r5, #5
40703770:	e5845060 	str	r5, [r4, #96]	; 0x60
40703774:	e1a00004 	mov	r0, r4
40703778:	e0823181 	add	r3, r2, r1, lsl #3
4070377c:	e5942040 	ldr	r2, [r4, #64]	; 0x40
40703780:	e0843003 	add	r3, r4, r3
40703784:	e5933008 	ldr	r3, [r3, #8]
40703788:	e5843048 	str	r3, [r4, #72]	; 0x48
4070378c:	e5923048 	ldr	r3, [r2, #72]	; 0x48
40703790:	e3c3300f 	bic	r3, r3, #15
40703794:	e1833005 	orr	r3, r3, r5
40703798:	e5823048 	str	r3, [r2, #72]	; 0x48
4070379c:	ebfffec5 	bl	407032b8 <ddr_hw_training_ctl>
407037a0:	e59d3000 	ldr	r3, [sp]
407037a4:	e3580002 	cmp	r8, #2
407037a8:	e0833000 	add	r3, r3, r0
407037ac:	e58d3000 	str	r3, [sp]
407037b0:	1affffd4 	bne	40703708 <ddr_hw_training+0xd4>
407037b4:	e594305c 	ldr	r3, [r4, #92]	; 0x5c
407037b8:	e08a1205 	add	r1, sl, r5, lsl #4
407037bc:	e281100c 	add	r1, r1, #12
407037c0:	e3a02000 	mov	r2, #0
407037c4:	e023439b 	mla	r3, fp, r3, r4
407037c8:	e593c010 	ldr	ip, [r3, #16]
407037cc:	e5943040 	ldr	r3, [r4, #64]	; 0x40
407037d0:	e2833f8b 	add	r3, r3, #556	; 0x22c
407037d4:	e1a00003 	mov	r0, r3
407037d8:	e15c0002 	cmp	ip, r2
407037dc:	1a000004 	bne	407037f4 <ddr_hw_training+0x1c0>
407037e0:	e3550001 	cmp	r5, #1
407037e4:	13a01000 	movne	r1, #0
407037e8:	1a000008 	bne	40703810 <ddr_hw_training+0x1dc>
407037ec:	e2855001 	add	r5, r5, #1
407037f0:	eaffffae 	b	407036b0 <ddr_hw_training+0x7c>
407037f4:	e490e080 	ldr	lr, [r0], #128	; 0x80
407037f8:	e2822001 	add	r2, r2, #1
407037fc:	e5a1e004 	str	lr, [r1, #4]!
40703800:	eafffff4 	b	407037d8 <ddr_hw_training+0x1a4>
40703804:	e79a0101 	ldr	r0, [sl, r1, lsl #2]
40703808:	e2811001 	add	r1, r1, #1
4070380c:	e4830080 	str	r0, [r3], #128	; 0x80
40703810:	e1520001 	cmp	r2, r1
40703814:	1afffffa 	bne	40703804 <ddr_hw_training+0x1d0>
40703818:	eafffff3 	b	407037ec <ddr_hw_training+0x1b8>
4070381c:	e5b8c004 	ldr	ip, [r8, #4]!
40703820:	e5943040 	ldr	r3, [r4, #64]	; 0x40
40703824:	e7e8105c 	ubfx	r1, ip, #0, #9
40703828:	e5845054 	str	r5, [r4, #84]	; 0x54
4070382c:	e5980010 	ldr	r0, [r8, #16]
40703830:	e7e82050 	ubfx	r2, r0, #0, #9
40703834:	e1510002 	cmp	r1, r2
40703838:	82833f8b 	addhi	r3, r3, #556	; 0x22c
4070383c:	92833f8b 	addls	r3, r3, #556	; 0x22c
40703840:	80411002 	subhi	r1, r1, r2
40703844:	90421001 	subls	r1, r2, r1
40703848:	97830385 	strls	r0, [r3, r5, lsl #7]
4070384c:	e1a00004 	mov	r0, r4
40703850:	8783c385 	strhi	ip, [r3, r5, lsl #7]
40703854:	e2855001 	add	r5, r5, #1
40703858:	8584a060 	strhi	sl, [r4, #96]	; 0x60
4070385c:	9584b060 	strls	fp, [r4, #96]	; 0x60
40703860:	ebfffb3a 	bl	40702550 <ddr_rdqs_sync_rank_rdq>
40703864:	eaffffa0 	b	407036ec <ddr_hw_training+0xb8>
40703868:	e3a0300c 	mov	r3, #12
4070386c:	e28d1010 	add	r1, sp, #16
40703870:	e0235293 	mla	r3, r3, r2, r5
40703874:	e7911102 	ldr	r1, [r1, r2, lsl #2]
40703878:	e0843003 	add	r3, r4, r3
4070387c:	e5930014 	ldr	r0, [r3, #20]
40703880:	ebfff995 	bl	40701edc <ddr_training_set_timing>
40703884:	e2822001 	add	r2, r2, #1
40703888:	eaffffa3 	b	4070371c <ddr_hw_training+0xe8>

4070388c <ddr_vref_training>:
4070388c:	e92d45f0 	push	{r4, r5, r6, r7, r8, sl, lr}
40703890:	e1a04000 	mov	r4, r0
40703894:	e5903060 	ldr	r3, [r0, #96]	; 0x60
40703898:	e24ddf57 	sub	sp, sp, #348	; 0x15c
4070389c:	e5902040 	ldr	r2, [r0, #64]	; 0x40
407038a0:	e28d5004 	add	r5, sp, #4
407038a4:	e590e064 	ldr	lr, [r0, #100]	; 0x64
407038a8:	e1a0c503 	lsl	ip, r3, #10
407038ac:	e2823f87 	add	r3, r2, #540	; 0x21c
407038b0:	e082100c 	add	r1, r2, ip
407038b4:	e083300c 	add	r3, r3, ip
407038b8:	e594c05c 	ldr	ip, [r4, #92]	; 0x5c
407038bc:	e3a0203c 	mov	r2, #60	; 0x3c
407038c0:	e1a0640e 	lsl	r6, lr, #8
407038c4:	e0860001 	add	r0, r6, r1
407038c8:	e2811e21 	add	r1, r1, #528	; 0x210
407038cc:	e00c0c92 	mul	ip, r2, ip
407038d0:	e3a0200c 	mov	r2, #12
407038d4:	e022ce92 	mla	r2, r2, lr, ip
407038d8:	e2800e21 	add	r0, r0, #528	; 0x210
407038dc:	e0833006 	add	r3, r3, r6
407038e0:	e0842002 	add	r2, r4, r2
407038e4:	e5922018 	ldr	r2, [r2, #24]
407038e8:	e082e08e 	add	lr, r2, lr, lsl #1
407038ec:	e1a02005 	mov	r2, r5
407038f0:	e081138e 	add	r1, r1, lr, lsl #7
407038f4:	e1510000 	cmp	r1, r0
407038f8:	1a00002e 	bne	407039b8 <ddr_vref_training+0x12c>
407038fc:	e3a02f41 	mov	r2, #260	; 0x104
40703900:	e3a01000 	mov	r1, #0
40703904:	e28d0054 	add	r0, sp, #84	; 0x54
40703908:	ebfff8fb 	bl	40701cfc <ddrtr_memset>
4070390c:	e5943050 	ldr	r3, [r4, #80]	; 0x50
40703910:	e3530001 	cmp	r3, #1
40703914:	03a06000 	moveq	r6, #0
40703918:	03a0700c 	moveq	r7, #12
4070391c:	03a0803c 	moveq	r8, #60	; 0x3c
40703920:	0a00003d 	beq	40703a1c <ddr_vref_training+0x190>
40703924:	e594305c 	ldr	r3, [r4, #92]	; 0x5c
40703928:	e3a0203c 	mov	r2, #60	; 0x3c
4070392c:	e5941060 	ldr	r1, [r4, #96]	; 0x60
40703930:	e0234392 	mla	r3, r2, r3, r4
40703934:	e5932004 	ldr	r2, [r3, #4]
40703938:	e5943044 	ldr	r3, [r4, #68]	; 0x44
4070393c:	e2833060 	add	r3, r3, #96	; 0x60
40703940:	e7937101 	ldr	r7, [r3, r1, lsl #2]
40703944:	e2423006 	sub	r3, r2, #6
40703948:	e3d33004 	bics	r3, r3, #4
4070394c:	1a00004b 	bne	40703a80 <ddr_vref_training+0x1f4>
40703950:	e3520006 	cmp	r2, #6
40703954:	e3a06000 	mov	r6, #0
40703958:	17e17557 	ubfxne	r7, r7, #10, #2
4070395c:	e3a0800c 	mov	r8, #12
40703960:	03a07001 	moveq	r7, #1
40703964:	e3a0a03c 	mov	sl, #60	; 0x3c
40703968:	e594305c 	ldr	r3, [r4, #92]	; 0x5c
4070396c:	e5942064 	ldr	r2, [r4, #100]	; 0x64
40703970:	e003039a 	mul	r3, sl, r3
40703974:	e0233298 	mla	r3, r8, r2, r3
40703978:	e0843003 	add	r3, r4, r3
4070397c:	e5933018 	ldr	r3, [r3, #24]
40703980:	e1530006 	cmp	r3, r6
40703984:	9a00002c 	bls	40703a3c <ddr_vref_training+0x1b0>
40703988:	e3570001 	cmp	r7, #1
4070398c:	e0862082 	add	r2, r6, r2, lsl #1
40703990:	e5842054 	str	r2, [r4, #84]	; 0x54
40703994:	1a000002 	bne	407039a4 <ddr_vref_training+0x118>
40703998:	e3c63002 	bic	r3, r6, #2
4070399c:	e3530001 	cmp	r3, #1
407039a0:	0a000002 	beq	407039b0 <ddr_vref_training+0x124>
407039a4:	e28d1054 	add	r1, sp, #84	; 0x54
407039a8:	e1a00004 	mov	r0, r4
407039ac:	ebfffd1b 	bl	40702e20 <ddr_vref_cal>
407039b0:	e2866001 	add	r6, r6, #1
407039b4:	eaffffeb 	b	40703968 <ddr_vref_training+0xdc>
407039b8:	e594c050 	ldr	ip, [r4, #80]	; 0x50
407039bc:	e2800080 	add	r0, r0, #128	; 0x80
407039c0:	e2822004 	add	r2, r2, #4
407039c4:	e2833080 	add	r3, r3, #128	; 0x80
407039c8:	e35c0002 	cmp	ip, #2
407039cc:	0510c080 	ldreq	ip, [r0, #-128]	; 0xffffff80
407039d0:	1513c080 	ldrne	ip, [r3, #-128]	; 0xffffff80
407039d4:	0502c004 	streq	ip, [r2, #-4]
407039d8:	0510c07c 	ldreq	ip, [r0, #-124]	; 0xffffff84
407039dc:	1502c004 	strne	ip, [r2, #-4]
407039e0:	1513c07c 	ldrne	ip, [r3, #-124]	; 0xffffff84
407039e4:	0582c00c 	streq	ip, [r2, #12]
407039e8:	0510c078 	ldreq	ip, [r0, #-120]	; 0xffffff88
407039ec:	1582c00c 	strne	ip, [r2, #12]
407039f0:	0582c03c 	streq	ip, [r2, #60]	; 0x3c
407039f4:	eaffffbe 	b	407038f4 <ddr_vref_training+0x68>
407039f8:	e0862082 	add	r2, r6, r2, lsl #1
407039fc:	e5842054 	str	r2, [r4, #84]	; 0x54
40703a00:	e3c22002 	bic	r2, r2, #2
40703a04:	e3520001 	cmp	r2, #1
40703a08:	0a000002 	beq	40703a18 <ddr_vref_training+0x18c>
40703a0c:	e28d1054 	add	r1, sp, #84	; 0x54
40703a10:	e1a00004 	mov	r0, r4
40703a14:	ebfffd01 	bl	40702e20 <ddr_vref_cal>
40703a18:	e2866001 	add	r6, r6, #1
40703a1c:	e594305c 	ldr	r3, [r4, #92]	; 0x5c
40703a20:	e5942064 	ldr	r2, [r4, #100]	; 0x64
40703a24:	e0030398 	mul	r3, r8, r3
40703a28:	e0233297 	mla	r3, r7, r2, r3
40703a2c:	e0843003 	add	r3, r4, r3
40703a30:	e5933018 	ldr	r3, [r3, #24]
40703a34:	e1530006 	cmp	r3, r6
40703a38:	8affffee 	bhi	407039f8 <ddr_vref_training+0x16c>
40703a3c:	e5943060 	ldr	r3, [r4, #96]	; 0x60
40703a40:	e3a01000 	mov	r1, #0
40703a44:	e5940040 	ldr	r0, [r4, #64]	; 0x40
40703a48:	e3a0c00c 	mov	ip, #12
40703a4c:	e3a0e03c 	mov	lr, #60	; 0x3c
40703a50:	e0800503 	add	r0, r0, r3, lsl #10
40703a54:	e594205c 	ldr	r2, [r4, #92]	; 0x5c
40703a58:	e5943064 	ldr	r3, [r4, #100]	; 0x64
40703a5c:	e002029e 	mul	r2, lr, r2
40703a60:	e022239c 	mla	r2, ip, r3, r2
40703a64:	e0842002 	add	r2, r4, r2
40703a68:	e5922018 	ldr	r2, [r2, #24]
40703a6c:	e1510002 	cmp	r1, r2
40703a70:	3a000005 	bcc	40703a8c <ddr_vref_training+0x200>
40703a74:	e28d1054 	add	r1, sp, #84	; 0x54
40703a78:	e1a00004 	mov	r0, r4
40703a7c:	eb000110 	bl	40703ec4 <ddr_result_data_save>
40703a80:	e3a00000 	mov	r0, #0
40703a84:	e28ddf57 	add	sp, sp, #348	; 0x15c
40703a88:	e8bd85f0 	pop	{r4, r5, r6, r7, r8, sl, pc}
40703a8c:	e5942050 	ldr	r2, [r4, #80]	; 0x50
40703a90:	e0813083 	add	r3, r1, r3, lsl #1
40703a94:	e2855004 	add	r5, r5, #4
40703a98:	e2811001 	add	r1, r1, #1
40703a9c:	e3520002 	cmp	r2, #2
40703aa0:	e1a03383 	lsl	r3, r3, #7
40703aa4:	e5152004 	ldr	r2, [r5, #-4]
40703aa8:	e0833000 	add	r3, r3, r0
40703aac:	05832210 	streq	r2, [r3, #528]	; 0x210
40703ab0:	0595200c 	ldreq	r2, [r5, #12]
40703ab4:	1583221c 	strne	r2, [r3, #540]	; 0x21c
40703ab8:	1595200c 	ldrne	r2, [r5, #12]
40703abc:	05832214 	streq	r2, [r3, #532]	; 0x214
40703ac0:	0595203c 	ldreq	r2, [r5, #60]	; 0x3c
40703ac4:	15832220 	strne	r2, [r3, #544]	; 0x220
40703ac8:	05832218 	streq	r2, [r3, #536]	; 0x218
40703acc:	eaffffe0 	b	40703a54 <ddr_vref_training+0x1c8>

40703ad0 <ddr_vref_training_func>:
40703ad0:	e92d4030 	push	{r4, r5, lr}
40703ad4:	e24dd03c 	sub	sp, sp, #60	; 0x3c
40703ad8:	e1a04000 	mov	r4, r0
40703adc:	e3a02401 	mov	r2, #16777216	; 0x1000000
40703ae0:	e1a0100d 	mov	r1, sp
40703ae4:	ebfffa05 	bl	40702300 <ddr_training_save_reg>
40703ae8:	e1a00004 	mov	r0, r4
40703aec:	ebfff9dd 	bl	40702268 <ddr_training_switch_axi>
40703af0:	e3a01002 	mov	r1, #2
40703af4:	e1a00004 	mov	r0, r4
40703af8:	ebfffb12 	bl	40702748 <ddr_ddrt_init>
40703afc:	e5942048 	ldr	r2, [r4, #72]	; 0x48
40703b00:	e3a03001 	mov	r3, #1
40703b04:	e584306c 	str	r3, [r4, #108]	; 0x6c
40703b08:	e3120401 	tst	r2, #16777216	; 0x1000000
40703b0c:	0a000009 	beq	40703b38 <ddr_vref_training_func+0x68>
40703b10:	e3a05000 	mov	r5, #0
40703b14:	e5943048 	ldr	r3, [r4, #72]	; 0x48
40703b18:	e3130402 	tst	r3, #33554432	; 0x2000000
40703b1c:	0a00000a 	beq	40703b4c <ddr_vref_training_func+0x7c>
40703b20:	e1a00004 	mov	r0, r4
40703b24:	e1a0100d 	mov	r1, sp
40703b28:	ebfffa31 	bl	407023f4 <ddr_training_restore_reg>
40703b2c:	e1a00005 	mov	r0, r5
40703b30:	e28dd03c 	add	sp, sp, #60	; 0x3c
40703b34:	e8bd8030 	pop	{r4, r5, pc}
40703b38:	e5843050 	str	r3, [r4, #80]	; 0x50
40703b3c:	e1a00004 	mov	r0, r4
40703b40:	ebffff51 	bl	4070388c <ddr_vref_training>
40703b44:	e1a05000 	mov	r5, r0
40703b48:	eafffff1 	b	40703b14 <ddr_vref_training_func+0x44>
40703b4c:	e3a03002 	mov	r3, #2
40703b50:	e1a00004 	mov	r0, r4
40703b54:	e5843050 	str	r3, [r4, #80]	; 0x50
40703b58:	ebffff4b 	bl	4070388c <ddr_vref_training>
40703b5c:	e0855000 	add	r5, r5, r0
40703b60:	eaffffee 	b	40703b20 <ddr_vref_training_func+0x50>

40703b64 <ddr_wl_func>:
40703b64:	e3a00000 	mov	r0, #0
40703b68:	e12fff1e 	bx	lr

40703b6c <ddr_gating_func>:
40703b6c:	e3a00000 	mov	r0, #0
40703b70:	e12fff1e 	bx	lr

40703b74 <ddr_ac_training_func>:
40703b74:	e3a00000 	mov	r0, #0
40703b78:	e12fff1e 	bx	lr

40703b7c <ddr_lpca_training_func>:
40703b7c:	e3a00000 	mov	r0, #0
40703b80:	e12fff1e 	bx	lr

40703b84 <ddr_dcc_training_func>:
40703b84:	e3a00000 	mov	r0, #0
40703b88:	e12fff1e 	bx	lr

40703b8c <ddr_pcode_training>:
40703b8c:	e92d4df0 	push	{r4, r5, r6, r7, r8, sl, fp, lr}
40703b90:	e3a07000 	mov	r7, #0
40703b94:	e59fb140 	ldr	fp, [pc, #320]	; 40703cdc <ddr_pcode_training+0x150>
40703b98:	e24dd040 	sub	sp, sp, #64	; 0x40
40703b9c:	e1a06000 	mov	r6, r0
40703ba0:	e1a0a000 	mov	sl, r0
40703ba4:	e1a08007 	mov	r8, r7
40703ba8:	e596203c 	ldr	r2, [r6, #60]	; 0x3c
40703bac:	e1520007 	cmp	r2, r7
40703bb0:	8a000002 	bhi	40703bc0 <ddr_pcode_training+0x34>
40703bb4:	e1a00008 	mov	r0, r8
40703bb8:	e28dd040 	add	sp, sp, #64	; 0x40
40703bbc:	e8bd8df0 	pop	{r4, r5, r6, r7, r8, sl, fp, pc}
40703bc0:	e586705c 	str	r7, [r6, #92]	; 0x5c
40703bc4:	e3a05001 	mov	r5, #1
40703bc8:	e59a2000 	ldr	r2, [sl]
40703bcc:	e1a05715 	lsl	r5, r5, r7
40703bd0:	e3855701 	orr	r5, r5, #262144	; 0x40000
40703bd4:	e5862040 	str	r2, [r6, #64]	; 0x40
40703bd8:	e59a202c 	ldr	r2, [sl, #44]	; 0x2c
40703bdc:	e0155002 	ands	r5, r5, r2
40703be0:	e5862048 	str	r2, [r6, #72]	; 0x48
40703be4:	1a000039 	bne	40703cd0 <ddr_pcode_training+0x144>
40703be8:	e3a02701 	mov	r2, #262144	; 0x40000
40703bec:	e28d1008 	add	r1, sp, #8
40703bf0:	e1a00006 	mov	r0, r6
40703bf4:	ebfff9c1 	bl	40702300 <ddr_training_save_reg>
40703bf8:	e5964040 	ldr	r4, [r6, #64]	; 0x40
40703bfc:	e301204c 	movw	r2, #4172	; 0x104c
40703c00:	e59fc0d8 	ldr	ip, [pc, #216]	; 40703ce0 <ddr_pcode_training+0x154>
40703c04:	e0840002 	add	r0, r4, r2
40703c08:	e7941002 	ldr	r1, [r4, r2]
40703c0c:	e3811001 	orr	r1, r1, #1
40703c10:	e7841002 	str	r1, [r4, r2]
40703c14:	e590e000 	ldr	lr, [r0]
40703c18:	e2855001 	add	r5, r5, #1
40703c1c:	e155000c 	cmp	r5, ip
40703c20:	83a01000 	movhi	r1, #0
40703c24:	93a01001 	movls	r1, #1
40703c28:	e1d137ae 	bics	r3, r1, lr, lsr #15
40703c2c:	e58d3004 	str	r3, [sp, #4]
40703c30:	1afffff7 	bne	40703c14 <ddr_pcode_training+0x88>
40703c34:	e155000c 	cmp	r5, ip
40703c38:	83e01000 	mvnhi	r1, #0
40703c3c:	8a00001f 	bhi	40703cc0 <ddr_pcode_training+0x134>
40703c40:	e7945002 	ldr	r5, [r4, r2]
40703c44:	e7940002 	ldr	r0, [r4, r2]
40703c48:	e3c00001 	bic	r0, r0, #1
40703c4c:	e7840002 	str	r0, [r4, r2]
40703c50:	eb0000d7 	bl	40703fb4 <ddr_get_cksel>
40703c54:	e1a05825 	lsr	r5, r5, #16
40703c58:	e3a02059 	mov	r2, #89	; 0x59
40703c5c:	e59f3080 	ldr	r3, [pc, #128]	; 40703ce4 <ddr_pcode_training+0x158>
40703c60:	e0020592 	mul	r2, r2, r5
40703c64:	e0000290 	mul	r0, r0, r2
40703c68:	e59f2078 	ldr	r2, [pc, #120]	; 40703ce8 <ddr_pcode_training+0x15c>
40703c6c:	e0810390 	umull	r0, r1, r0, r3
40703c70:	e5940028 	ldr	r0, [r4, #40]	; 0x28
40703c74:	e3c0083f 	bic	r0, r0, #4128768	; 0x3f0000
40703c78:	e04222a1 	sub	r2, r2, r1, lsr #5
40703c7c:	e59d1004 	ldr	r1, [sp, #4]
40703c80:	e0832b92 	umull	r2, r3, r2, fp
40703c84:	e1a026a3 	lsr	r2, r3, #13
40703c88:	e3520024 	cmp	r2, #36	; 0x24
40703c8c:	23a02024 	movcs	r2, #36	; 0x24
40703c90:	e3520014 	cmp	r2, #20
40703c94:	33a02014 	movcc	r2, #20
40703c98:	e1800802 	orr	r0, r0, r2, lsl #16
40703c9c:	e5840028 	str	r0, [r4, #40]	; 0x28
40703ca0:	e594c170 	ldr	ip, [r4, #368]	; 0x170
40703ca4:	e3cc0c01 	bic	r0, ip, #256	; 0x100
40703ca8:	e5840170 	str	r0, [r4, #368]	; 0x170
40703cac:	e5940174 	ldr	r0, [r4, #372]	; 0x174
40703cb0:	e3c0043f 	bic	r0, r0, #1056964608	; 0x3f000000
40703cb4:	e1802c02 	orr	r2, r0, r2, lsl #24
40703cb8:	e5842174 	str	r2, [r4, #372]	; 0x174
40703cbc:	e584c170 	str	ip, [r4, #368]	; 0x170
40703cc0:	e0888001 	add	r8, r8, r1
40703cc4:	e1a00006 	mov	r0, r6
40703cc8:	e28d1008 	add	r1, sp, #8
40703ccc:	ebfff9c8 	bl	407023f4 <ddr_training_restore_reg>
40703cd0:	e2877001 	add	r7, r7, #1
40703cd4:	e28aa03c 	add	sl, sl, #60	; 0x3c
40703cd8:	eaffffb2 	b	40703ba8 <ddr_pcode_training+0x1c>
40703cdc:	d1b71759 	.word	0xd1b71759
40703ce0:	0001869f 	.word	0x0001869f
40703ce4:	1b4e81b5 	.word	0x1b4e81b5
40703ce8:	00077dd0 	.word	0x00077dd0

40703cec <ddr_training_console_if>:
40703cec:	e3a00000 	mov	r0, #0
40703cf0:	e12fff1e 	bx	lr

40703cf4 <ddr_training_boot_func>:
40703cf4:	e92d4030 	push	{r4, r5, lr}
40703cf8:	e1a04000 	mov	r4, r0
40703cfc:	e5900040 	ldr	r0, [r0, #64]	; 0x40
40703d00:	e24dd03c 	sub	sp, sp, #60	; 0x3c
40703d04:	e2800008 	add	r0, r0, #8
40703d08:	ebfff7ef 	bl	40701ccc <ddr_read>
40703d0c:	e3100020 	tst	r0, #32
40703d10:	0a000004 	beq	40703d28 <ddr_training_boot_func+0x34>
40703d14:	e3e03000 	mvn	r3, #0
40703d18:	e5941040 	ldr	r1, [r4, #64]	; 0x40
40703d1c:	e1a02003 	mov	r2, r3
40703d20:	e3a00002 	mov	r0, #2
40703d24:	ebfff8e6 	bl	407020c4 <ddr_training_stat>
40703d28:	e1a00004 	mov	r0, r4
40703d2c:	ebffff92 	bl	40703b7c <ddr_lpca_training_func>
40703d30:	e1a05000 	mov	r5, r0
40703d34:	e1a00004 	mov	r0, r4
40703d38:	ebffff89 	bl	40703b64 <ddr_wl_func>
40703d3c:	e0855000 	add	r5, r5, r0
40703d40:	e1a00004 	mov	r0, r4
40703d44:	ebfffd22 	bl	407031d4 <ddr_dataeye_training_func>
40703d48:	e0955000 	adds	r5, r5, r0
40703d4c:	0a000013 	beq	40703da0 <ddr_training_boot_func+0xac>
40703d50:	e3a01601 	mov	r1, #1048576	; 0x100000
40703d54:	e1a00004 	mov	r0, r4
40703d58:	ebfff93b 	bl	4070224c <ddr_training_check_bypass>
40703d5c:	e3500000 	cmp	r0, #0
40703d60:	1a00000e 	bne	40703da0 <ddr_training_boot_func+0xac>
40703d64:	e3a02601 	mov	r2, #1048576	; 0x100000
40703d68:	e1a0100d 	mov	r1, sp
40703d6c:	e1a00004 	mov	r0, r4
40703d70:	ebfff962 	bl	40702300 <ddr_training_save_reg>
40703d74:	e1a00004 	mov	r0, r4
40703d78:	ebfffd30 	bl	40703240 <ddr_hw_dataeye_read>
40703d7c:	e1a0100d 	mov	r1, sp
40703d80:	e1a05000 	mov	r5, r0
40703d84:	e1a00004 	mov	r0, r4
40703d88:	ebfff999 	bl	407023f4 <ddr_training_restore_reg>
40703d8c:	e3a03001 	mov	r3, #1
40703d90:	e1a00004 	mov	r0, r4
40703d94:	e5843068 	str	r3, [r4, #104]	; 0x68
40703d98:	ebfffcf2 	bl	40703168 <ddr_dataeye_training>
40703d9c:	e0855000 	add	r5, r5, r0
40703da0:	e1a00004 	mov	r0, r4
40703da4:	ebffff70 	bl	40703b6c <ddr_gating_func>
40703da8:	e0855000 	add	r5, r5, r0
40703dac:	e1a00004 	mov	r0, r4
40703db0:	ebffff46 	bl	40703ad0 <ddr_vref_training_func>
40703db4:	e0850000 	add	r0, r5, r0
40703db8:	e28dd03c 	add	sp, sp, #60	; 0x3c
40703dbc:	e8bd8030 	pop	{r4, r5, pc}

40703dc0 <ddr_sw_training_func>:
40703dc0:	e92d4030 	push	{r4, r5, lr}
40703dc4:	e24dd07c 	sub	sp, sp, #124	; 0x7c
40703dc8:	e59f0098 	ldr	r0, [pc, #152]	; 40703e68 <ddr_sw_training_func+0xa8>
40703dcc:	ebfff7be 	bl	40701ccc <ddr_read>
40703dd0:	e59f1090 	ldr	r1, [pc, #144]	; 40703e68 <ddr_sw_training_func+0xa8>
40703dd4:	e1a00820 	lsr	r0, r0, #16
40703dd8:	e1a00800 	lsl	r0, r0, #16
40703ddc:	e3800f85 	orr	r0, r0, #532	; 0x214
40703de0:	e3800002 	orr	r0, r0, #2
40703de4:	ebfff7ba 	bl	40701cd4 <ddr_write>
40703de8:	e59f007c 	ldr	r0, [pc, #124]	; 40703e6c <ddr_sw_training_func+0xac>
40703dec:	ebfff7b6 	bl	40701ccc <ddr_read>
40703df0:	e3700001 	cmn	r0, #1
40703df4:	0a000012 	beq	40703e44 <ddr_sw_training_func+0x84>
40703df8:	eb000037 	bl	40703edc <ddr_training_start>
40703dfc:	e59f106c 	ldr	r1, [pc, #108]	; 40703e70 <ddr_sw_training_func+0xb0>
40703e00:	e3a00000 	mov	r0, #0
40703e04:	e3a05000 	mov	r5, #0
40703e08:	ebfff7b1 	bl	40701cd4 <ddr_write>
40703e0c:	e1a0000d 	mov	r0, sp
40703e10:	ebfffa40 	bl	40702718 <ddr_training_cfg_init>
40703e14:	e1a0000d 	mov	r0, sp
40703e18:	e58d5070 	str	r5, [sp, #112]	; 0x70
40703e1c:	ebfff801 	bl	40701e28 <ddr_training_all>
40703e20:	e1a04000 	mov	r4, r0
40703e24:	e1a0000d 	mov	r0, sp
40703e28:	ebffff55 	bl	40703b84 <ddr_dcc_training_func>
40703e2c:	e0944000 	adds	r4, r4, r0
40703e30:	1a000009 	bne	40703e5c <ddr_sw_training_func+0x9c>
40703e34:	eb000027 	bl	40703ed8 <ddr_training_suc>
40703e38:	e1a00004 	mov	r0, r4
40703e3c:	e28dd07c 	add	sp, sp, #124	; 0x7c
40703e40:	e8bd8030 	pop	{r4, r5, pc}
40703e44:	e59f0028 	ldr	r0, [pc, #40]	; 40703e74 <ddr_sw_training_func+0xb4>
40703e48:	ebfff79f 	bl	40701ccc <ddr_read>
40703e4c:	e3700001 	cmn	r0, #1
40703e50:	1affffe8 	bne	40703df8 <ddr_sw_training_func+0x38>
40703e54:	e3a04000 	mov	r4, #0
40703e58:	eafffff6 	b	40703e38 <ddr_sw_training_func+0x78>
40703e5c:	e1a00005 	mov	r0, r5
40703e60:	ebffffa1 	bl	40703cec <ddr_training_console_if>
40703e64:	eafffff3 	b	40703e38 <ddr_sw_training_func+0x78>
40703e68:	120200b4 	.word	0x120200b4
40703e6c:	120200a0 	.word	0x120200a0
40703e70:	120200b0 	.word	0x120200b0
40703e74:	120200a4 	.word	0x120200a4

40703e78 <ddr_pcode_training_func>:
40703e78:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
40703e7c:	e24dd07c 	sub	sp, sp, #124	; 0x7c
40703e80:	e1a0000d 	mov	r0, sp
40703e84:	ebfffa23 	bl	40702718 <ddr_training_cfg_init>
40703e88:	e1a0000d 	mov	r0, sp
40703e8c:	ebffff3e 	bl	40703b8c <ddr_pcode_training>
40703e90:	e28dd07c 	add	sp, sp, #124	; 0x7c
40703e94:	e49df004 	pop	{pc}		; (ldr pc, [sp], #4)

40703e98 <ddr_hw_training_func>:
40703e98:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
40703e9c:	e24dd07c 	sub	sp, sp, #124	; 0x7c
40703ea0:	e1a0000d 	mov	r0, sp
40703ea4:	ebfffa1b 	bl	40702718 <ddr_training_cfg_init>
40703ea8:	e1a0000d 	mov	r0, sp
40703eac:	ebfffde0 	bl	40703634 <ddr_hw_training>
40703eb0:	e28dd07c 	add	sp, sp, #124	; 0x7c
40703eb4:	e49df004 	pop	{pc}		; (ldr pc, [sp], #4)

40703eb8 <ddr_sw_training_if>:
40703eb8:	eaffffc0 	b	40703dc0 <ddr_sw_training_func>

40703ebc <ddr_hw_training_if>:
40703ebc:	eafffff5 	b	40703e98 <ddr_hw_training_func>

40703ec0 <ddr_pcode_training_if>:
40703ec0:	eaffffec 	b	40703e78 <ddr_pcode_training_func>

40703ec4 <ddr_result_data_save>:
40703ec4:	e12fff1e 	bx	lr

40703ec8 <ddr_lpca_data_save>:
40703ec8:	e12fff1e 	bx	lr

40703ecc <ddr_ddrt_get_test_addr>:
40703ecc:	e3a00101 	mov	r0, #1073741824	; 0x40000000
40703ed0:	e12fff1e 	bx	lr

40703ed4 <ddr_training_error>:
40703ed4:	e12fff1e 	bx	lr

40703ed8 <ddr_training_suc>:
40703ed8:	e12fff1e 	bx	lr

40703edc <ddr_training_start>:
40703edc:	e12fff1e 	bx	lr

40703ee0 <ddr_cmd_prepare_copy>:
40703ee0:	e12fff1e 	bx	lr

40703ee4 <ddr_cmd_site_save>:
40703ee4:	e92d4070 	push	{r4, r5, r6, lr}
40703ee8:	e59f4070 	ldr	r4, [pc, #112]	; 40703f60 <ddr_cmd_site_save+0x7c>
40703eec:	e59f5070 	ldr	r5, [pc, #112]	; 40703f64 <ddr_cmd_site_save+0x80>
40703ef0:	e1a00004 	mov	r0, r4
40703ef4:	ebfff774 	bl	40701ccc <ddr_read>
40703ef8:	e1a01004 	mov	r1, r4
40703efc:	e2444b5f 	sub	r4, r4, #97280	; 0x17c00
40703f00:	e2444f9e 	sub	r4, r4, #632	; 0x278
40703f04:	e585001c 	str	r0, [r5, #28]
40703f08:	e3c00020 	bic	r0, r0, #32
40703f0c:	ebfff770 	bl	40701cd4 <ddr_write>
40703f10:	e1a00004 	mov	r0, r4
40703f14:	ebfff76c 	bl	40701ccc <ddr_read>
40703f18:	e1a01004 	mov	r1, r4
40703f1c:	e5850020 	str	r0, [r5, #32]
40703f20:	e3800002 	orr	r0, r0, #2
40703f24:	ebfff76a 	bl	40701cd4 <ddr_write>
40703f28:	e320f000 	nop	{0}
40703f2c:	e1a00004 	mov	r0, r4
40703f30:	ebfff765 	bl	40701ccc <ddr_read>
40703f34:	e1a01004 	mov	r1, r4
40703f38:	e59f4028 	ldr	r4, [pc, #40]	; 40703f68 <ddr_cmd_site_save+0x84>
40703f3c:	e3c00001 	bic	r0, r0, #1
40703f40:	ebfff763 	bl	40701cd4 <ddr_write>
40703f44:	e1a00004 	mov	r0, r4
40703f48:	ebfff75f 	bl	40701ccc <ddr_read>
40703f4c:	e1a01004 	mov	r1, r4
40703f50:	e5850024 	str	r0, [r5, #36]	; 0x24
40703f54:	e3c00102 	bic	r0, r0, #-2147483648	; 0x80000000
40703f58:	e8bd4070 	pop	{r4, r5, r6, lr}
40703f5c:	eafff75c 	b	40701cd4 <ddr_write>
40703f60:	12028010 	.word	0x12028010
40703f64:	4073b18c 	.word	0x4073b18c
40703f68:	120dc0b0 	.word	0x120dc0b0

40703f6c <ddr_cmd_site_restore>:
40703f6c:	e92d4010 	push	{r4, lr}
40703f70:	e59f4024 	ldr	r4, [pc, #36]	; 40703f9c <ddr_cmd_site_restore+0x30>
40703f74:	e59f1024 	ldr	r1, [pc, #36]	; 40703fa0 <ddr_cmd_site_restore+0x34>
40703f78:	e594001c 	ldr	r0, [r4, #28]
40703f7c:	ebfff754 	bl	40701cd4 <ddr_write>
40703f80:	e5940020 	ldr	r0, [r4, #32]
40703f84:	e59f1018 	ldr	r1, [pc, #24]	; 40703fa4 <ddr_cmd_site_restore+0x38>
40703f88:	ebfff751 	bl	40701cd4 <ddr_write>
40703f8c:	e5940024 	ldr	r0, [r4, #36]	; 0x24
40703f90:	e59f1010 	ldr	r1, [pc, #16]	; 40703fa8 <ddr_cmd_site_restore+0x3c>
40703f94:	e8bd4010 	pop	{r4, lr}
40703f98:	eafff74d 	b	40701cd4 <ddr_write>
40703f9c:	4073b18c 	.word	0x4073b18c
40703fa0:	12028010 	.word	0x12028010
40703fa4:	12010198 	.word	0x12010198
40703fa8:	120dc0b0 	.word	0x120dc0b0

40703fac <ddr_training_save_reg_custom>:
40703fac:	e12fff1e 	bx	lr

40703fb0 <ddr_training_restore_reg_custom>:
40703fb0:	e12fff1e 	bx	lr

40703fb4 <ddr_get_cksel>:
40703fb4:	e92d4010 	push	{r4, lr}
40703fb8:	e59f0024 	ldr	r0, [pc, #36]	; 40703fe4 <ddr_get_cksel+0x30>
40703fbc:	ebfff742 	bl	40701ccc <ddr_read>
40703fc0:	e7e201d0 	ubfx	r0, r0, #3, #3
40703fc4:	e3500000 	cmp	r0, #0
40703fc8:	0a000003 	beq	40703fdc <ddr_get_cksel+0x28>
40703fcc:	e3500001 	cmp	r0, #1
40703fd0:	e30001c2 	movw	r0, #450	; 0x1c2
40703fd4:	13a00f4b 	movne	r0, #300	; 0x12c
40703fd8:	e8bd8010 	pop	{r4, pc}
40703fdc:	e3a00018 	mov	r0, #24
40703fe0:	e8bd8010 	pop	{r4, pc}
40703fe4:	12010080 	.word	0x12010080

40703fe8 <uart_early_init>:
40703fe8:	e59f3028 	ldr	r3, [pc, #40]	; 40704018 <uart_base_addr_L0>
40703fec:	e3a02000 	mov	r2, #0
40703ff0:	e5832030 	str	r2, [r3, #48]	; 0x30
40703ff4:	e282200d 	add	r2, r2, #13
40703ff8:	e5832024 	str	r2, [r3, #36]	; 0x24
40703ffc:	e3a02001 	mov	r2, #1
40704000:	e5832028 	str	r2, [r3, #40]	; 0x28
40704004:	e3a02070 	mov	r2, #112	; 0x70
40704008:	e583202c 	str	r2, [r3, #44]	; 0x2c
4070400c:	e59f2098 	ldr	r2, [pc, #152]	; 407040ac <uart_base_addr_L3+0x4>
40704010:	e5832030 	str	r2, [r3, #48]	; 0x30
40704014:	e12fff1e 	bx	lr

40704018 <uart_base_addr_L0>:
40704018:	12040000 	.word	0x12040000

4070401c <uart_early_puts>:
4070401c:	e59f1024 	ldr	r1, [pc, #36]	; 40704048 <uart_base_addr_L1>
40704020:	ea000004 	b	40704038 <next_char>

40704024 <output>:
40704024:	e5913018 	ldr	r3, [r1, #24]
40704028:	e3130020 	tst	r3, #32
4070402c:	1afffffc 	bne	40704024 <output>
40704030:	e5812000 	str	r2, [r1]
40704034:	e2800001 	add	r0, r0, #1

40704038 <next_char>:
40704038:	e5d02000 	ldrb	r2, [r0]
4070403c:	e3520000 	cmp	r2, #0
40704040:	1afffff7 	bne	40704024 <output>
40704044:	e12fff1e 	bx	lr

40704048 <uart_base_addr_L1>:
40704048:	12040000 	.word	0x12040000

4070404c <uart_early_put_hex>:
4070404c:	e59f1038 	ldr	r1, [pc, #56]	; 4070408c <uart_base_addr_L2>
40704050:	e3a0201c 	mov	r2, #28

40704054 <wait2>:
40704054:	e5913018 	ldr	r3, [r1, #24]
40704058:	e3130020 	tst	r3, #32
4070405c:	1afffffc 	bne	40704054 <wait2>
40704060:	e3a0300f 	mov	r3, #15
40704064:	e0033230 	and	r3, r3, r0, lsr r2
40704068:	e3530009 	cmp	r3, #9
4070406c:	d2833030 	addle	r3, r3, #48	; 0x30
40704070:	c2833037 	addgt	r3, r3, #55	; 0x37
40704074:	e5813000 	str	r3, [r1]
40704078:	e3520000 	cmp	r2, #0
4070407c:	0a000001 	beq	40704088 <exit2>
40704080:	e2422004 	sub	r2, r2, #4
40704084:	eafffff2 	b	40704054 <wait2>

40704088 <exit2>:
40704088:	e12fff1e 	bx	lr

4070408c <uart_base_addr_L2>:
4070408c:	12040000 	.word	0x12040000

40704090 <uart_early_putc>:
40704090:	e59f1010 	ldr	r1, [pc, #16]	; 407040a8 <uart_base_addr_L3>

40704094 <wait3>:
40704094:	e5913018 	ldr	r3, [r1, #24]
40704098:	e3130020 	tst	r3, #32
4070409c:	1afffffc 	bne	40704094 <wait3>
407040a0:	e5810000 	str	r0, [r1]
407040a4:	e12fff1e 	bx	lr

407040a8 <uart_base_addr_L3>:
407040a8:	12040000 	.word	0x12040000
407040ac:	00000301 	.word	0x00000301

407040b0 <__div0>:
407040b0:	ea000149 	b	407045dc <hang>

407040b4 <sdhci_check_int_status>:
407040b4:	e59f2040 	ldr	r2, [pc, #64]	; 407040fc <sdhci_check_int_status+0x48>
407040b8:	e59fc040 	ldr	ip, [pc, #64]	; 40704100 <sdhci_check_int_status+0x4c>
407040bc:	e5923030 	ldr	r3, [r2, #48]	; 0x30
407040c0:	e1100003 	tst	r0, r3
407040c4:	1a000008 	bne	407040ec <sdhci_check_int_status+0x38>
407040c8:	e2511001 	subs	r1, r1, #1
407040cc:	0a000008 	beq	407040f4 <sdhci_check_int_status+0x40>
407040d0:	e113000c 	tst	r3, ip
407040d4:	1a000006 	bne	407040f4 <sdhci_check_int_status+0x40>
407040d8:	e3023711 	movw	r3, #10001	; 0x2711
407040dc:	e2533001 	subs	r3, r3, #1
407040e0:	0afffff5 	beq	407040bc <sdhci_check_int_status+0x8>
407040e4:	e320f000 	nop	{0}
407040e8:	eafffffb 	b	407040dc <sdhci_check_int_status+0x28>
407040ec:	e3a00000 	mov	r0, #0
407040f0:	e12fff1e 	bx	lr
407040f4:	e3e00000 	mvn	r0, #0
407040f8:	e12fff1e 	bx	lr
407040fc:	10010000 	.word	0x10010000
40704100:	ffff8000 	.word	0xffff8000

40704104 <sdhci_read_boot_data>:
40704104:	e3510a06 	cmp	r1, #24576	; 0x6000
40704108:	8a000009 	bhi	40704134 <sdhci_read_boot_data+0x30>
4070410c:	e3c11003 	bic	r1, r1, #3
40704110:	e59f30ac 	ldr	r3, [pc, #172]	; 407041c4 <sdhci_read_boot_data+0xc0>
40704114:	e0801001 	add	r1, r0, r1
40704118:	e1500001 	cmp	r0, r1
4070411c:	1a000001 	bne	40704128 <sdhci_read_boot_data+0x24>
40704120:	e3a00000 	mov	r0, #0
40704124:	e12fff1e 	bx	lr
40704128:	e4932004 	ldr	r2, [r3], #4
4070412c:	e4802004 	str	r2, [r0], #4
40704130:	eafffff8 	b	40704118 <sdhci_read_boot_data+0x14>
40704134:	e59f3088 	ldr	r3, [pc, #136]	; 407041c4 <sdhci_read_boot_data+0xc0>
40704138:	e2402004 	sub	r2, r0, #4
4070413c:	e59fc084 	ldr	ip, [pc, #132]	; 407041c8 <sdhci_read_boot_data+0xc4>
40704140:	e92d41f0 	push	{r4, r5, r6, r7, r8, lr}
40704144:	e493e004 	ldr	lr, [r3], #4
40704148:	e153000c 	cmp	r3, ip
4070414c:	e5a2e004 	str	lr, [r2, #4]!
40704150:	1afffffb 	bne	40704144 <sdhci_read_boot_data+0x40>
40704154:	e2414a06 	sub	r4, r1, #24576	; 0x6000
40704158:	e59f706c 	ldr	r7, [pc, #108]	; 407041cc <sdhci_read_boot_data+0xc8>
4070415c:	e7e83054 	ubfx	r3, r4, #0, #9
40704160:	e2805a06 	add	r5, r0, #24576	; 0x6000
40704164:	e3530000 	cmp	r3, #0
40704168:	e1a044a4 	lsr	r4, r4, #9
4070416c:	12844001 	addne	r4, r4, #1
40704170:	e3a06000 	mov	r6, #0
40704174:	e3a01e7d 	mov	r1, #2000	; 0x7d0
40704178:	e3a00020 	mov	r0, #32
4070417c:	ebffffcc 	bl	407040b4 <sdhci_check_int_status>
40704180:	e3500000 	cmp	r0, #0
40704184:	1a00000c 	bne	407041bc <sdhci_read_boot_data+0xb8>
40704188:	e3a03020 	mov	r3, #32
4070418c:	e5873030 	str	r3, [r7, #48]	; 0x30
40704190:	e1a03005 	mov	r3, r5
40704194:	e2855c02 	add	r5, r5, #512	; 0x200
40704198:	e5972020 	ldr	r2, [r7, #32]
4070419c:	e4832004 	str	r2, [r3], #4
407041a0:	e1530005 	cmp	r3, r5
407041a4:	1afffffb 	bne	40704198 <sdhci_read_boot_data+0x94>
407041a8:	e2866001 	add	r6, r6, #1
407041ac:	e1560004 	cmp	r6, r4
407041b0:	1affffef 	bne	40704174 <sdhci_read_boot_data+0x70>
407041b4:	e3a00000 	mov	r0, #0
407041b8:	e8bd81f0 	pop	{r4, r5, r6, r7, r8, pc}
407041bc:	e3e00000 	mvn	r0, #0
407041c0:	e8bd81f0 	pop	{r4, r5, r6, r7, r8, pc}
407041c4:	04010500 	.word	0x04010500
407041c8:	04016500 	.word	0x04016500
407041cc:	10010000 	.word	0x10010000

407041d0 <emmc_boot_read>:
407041d0:	eaffffcb 	b	40704104 <sdhci_read_boot_data>

407041d4 <hw_dec_sop_eop_first_set>:
407041d4:	e59f2034 	ldr	r2, [pc, #52]	; 40704210 <hw_dec_sop_eop_first_set+0x3c>
407041d8:	e3500001 	cmp	r0, #1
407041dc:	e59f3030 	ldr	r3, [pc, #48]	; 40704214 <hw_dec_sop_eop_first_set+0x40>
407041e0:	13a01001 	movne	r1, #1
407041e4:	15821000 	strne	r1, [r2]
407041e8:	13a02000 	movne	r2, #0
407041ec:	05830000 	streq	r0, [r3]
407041f0:	15832000 	strne	r2, [r3]
407041f4:	e59f301c 	ldr	r3, [pc, #28]	; 40704218 <hw_dec_sop_eop_first_set+0x44>
407041f8:	05820000 	streq	r0, [r2]
407041fc:	e3a02000 	mov	r2, #0
40704200:	e5832000 	str	r2, [r3]
40704204:	e59f3010 	ldr	r3, [pc, #16]	; 4070421c <hw_dec_sop_eop_first_set+0x48>
40704208:	e5830000 	str	r0, [r3]
4070420c:	e12fff1e 	bx	lr
40704210:	4073b1d0 	.word	0x4073b1d0
40704214:	4073b1cc 	.word	0x4073b1cc
40704218:	4073b1c8 	.word	0x4073b1c8
4070421c:	4073b1c4 	.word	0x4073b1c4

40704220 <hw_dec_intr_proc>:
40704220:	e59f30a0 	ldr	r3, [pc, #160]	; 407042c8 <hw_dec_intr_proc+0xa8>
40704224:	e5931124 	ldr	r1, [r3, #292]	; 0x124
40704228:	f57ff05f 	dmb	sy
4070422c:	e3110002 	tst	r1, #2
40704230:	0a00000c 	beq	40704268 <hw_dec_intr_proc+0x48>
40704234:	e59f2090 	ldr	r2, [pc, #144]	; 407042cc <hw_dec_intr_proc+0xac>
40704238:	e5920080 	ldr	r0, [r2, #128]	; 0x80
4070423c:	f57ff05f 	dmb	sy
40704240:	e3500000 	cmp	r0, #0
40704244:	aa000002 	bge	40704254 <hw_dec_intr_proc+0x34>
40704248:	f57ff05f 	dmb	sy
4070424c:	e3a00001 	mov	r0, #1
40704250:	e5820090 	str	r0, [r2, #144]	; 0x90
40704254:	e5932130 	ldr	r2, [r3, #304]	; 0x130
40704258:	f57ff05f 	dmb	sy
4070425c:	e3822002 	orr	r2, r2, #2
40704260:	f57ff05f 	dmb	sy
40704264:	e5832130 	str	r2, [r3, #304]	; 0x130
40704268:	e3110001 	tst	r1, #1
4070426c:	0a000013 	beq	407042c0 <hw_dec_intr_proc+0xa0>
40704270:	e59f2054 	ldr	r2, [pc, #84]	; 407042cc <hw_dec_intr_proc+0xac>
40704274:	e5923084 	ldr	r3, [r2, #132]	; 0x84
40704278:	f57ff05f 	dmb	sy
4070427c:	e3530000 	cmp	r3, #0
40704280:	a3a00000 	movge	r0, #0
40704284:	aa000006 	bge	407042a4 <hw_dec_intr_proc+0x84>
40704288:	e6ef3073 	uxtb	r3, r3
4070428c:	e3530000 	cmp	r3, #0
40704290:	03a00000 	moveq	r0, #0
40704294:	13e00001 	mvnne	r0, #1
40704298:	f57ff05f 	dmb	sy
4070429c:	e3a03001 	mov	r3, #1
407042a0:	e5823094 	str	r3, [r2, #148]	; 0x94
407042a4:	e59f201c 	ldr	r2, [pc, #28]	; 407042c8 <hw_dec_intr_proc+0xa8>
407042a8:	e5923130 	ldr	r3, [r2, #304]	; 0x130
407042ac:	f57ff05f 	dmb	sy
407042b0:	e3833001 	orr	r3, r3, #1
407042b4:	f57ff05f 	dmb	sy
407042b8:	e5823130 	str	r3, [r2, #304]	; 0x130
407042bc:	e12fff1e 	bx	lr
407042c0:	e3e00000 	mvn	r0, #0
407042c4:	e12fff1e 	bx	lr
407042c8:	11310000 	.word	0x11310000
407042cc:	11312000 	.word	0x11312000

407042d0 <hw_dec_start>:
407042d0:	e59fc0a0 	ldr	ip, [pc, #160]	; 40704378 <hw_dec_start+0xa8>
407042d4:	e92d4010 	push	{r4, lr}
407042d8:	e59ce000 	ldr	lr, [ip]
407042dc:	e59d4010 	ldr	r4, [sp, #16]
407042e0:	e35e0000 	cmp	lr, #0
407042e4:	0a000006 	beq	40704304 <hw_dec_start+0x34>
407042e8:	e3540000 	cmp	r4, #0
407042ec:	e59fe088 	ldr	lr, [pc, #136]	; 4070437c <hw_dec_start+0xac>
407042f0:	1a000017 	bne	40704354 <hw_dec_start+0x84>
407042f4:	f57ff05f 	dmb	sy
407042f8:	e58e1020 	str	r1, [lr, #32]
407042fc:	f57ff05f 	dmb	sy
40704300:	e58e3024 	str	r3, [lr, #36]	; 0x24
40704304:	f57ff05f 	dmb	sy
40704308:	e59f106c 	ldr	r1, [pc, #108]	; 4070437c <hw_dec_start+0xac>
4070430c:	e3540000 	cmp	r4, #0
40704310:	e59f3068 	ldr	r3, [pc, #104]	; 40704380 <hw_dec_start+0xb0>
40704314:	e5810040 	str	r0, [r1, #64]	; 0x40
40704318:	e5933000 	ldr	r3, [r3]
4070431c:	e59c0000 	ldr	r0, [ip]
40704320:	e1a03e83 	lsl	r3, r3, #29
40704324:	e1833e00 	orr	r3, r3, r0, lsl #28
40704328:	e1832002 	orr	r2, r3, r2
4070432c:	03a03102 	moveq	r3, #-2147483648	; 0x80000000
40704330:	13a03000 	movne	r3, #0
40704334:	e1832002 	orr	r2, r3, r2
40704338:	f57ff05f 	dmb	sy
4070433c:	e5812044 	str	r2, [r1, #68]	; 0x44
40704340:	f57ff05f 	dmb	sy
40704344:	e59f3038 	ldr	r3, [pc, #56]	; 40704384 <hw_dec_start+0xb4>
40704348:	e59d2008 	ldr	r2, [sp, #8]
4070434c:	e5832000 	str	r2, [r3]
40704350:	e8bd8010 	pop	{r4, pc}
40704354:	f57ff05f 	dmb	sy
40704358:	e2833eff 	add	r3, r3, #4080	; 0xff0
4070435c:	e58e1028 	str	r1, [lr, #40]	; 0x28
40704360:	e283300f 	add	r3, r3, #15
40704364:	e1a03623 	lsr	r3, r3, #12
40704368:	e1a03103 	lsl	r3, r3, #2
4070436c:	f57ff05f 	dmb	sy
40704370:	e58e302c 	str	r3, [lr, #44]	; 0x2c
40704374:	eaffffe2 	b	40704304 <hw_dec_start+0x34>
40704378:	4073b1d0 	.word	0x4073b1d0
4070437c:	11312000 	.word	0x11312000
40704380:	4073b1cc 	.word	0x4073b1cc
40704384:	11314000 	.word	0x11314000

40704388 <hw_dec_wait_finish>:
40704388:	e92d4073 	push	{r0, r1, r4, r5, r6, lr}
4070438c:	e3a06000 	mov	r6, #0
40704390:	e59f4058 	ldr	r4, [pc, #88]	; 407043f0 <hw_dec_wait_finish+0x68>
40704394:	e3a01000 	mov	r1, #0
40704398:	e3a00056 	mov	r0, #86	; 0x56
4070439c:	ebffff9f 	bl	40704220 <hw_dec_intr_proc>
407043a0:	e2544001 	subs	r4, r4, #1
407043a4:	e1a05000 	mov	r5, r0
407043a8:	1a000004 	bne	407043c0 <hw_dec_wait_finish+0x38>
407043ac:	e59f0040 	ldr	r0, [pc, #64]	; 407043f4 <hw_dec_wait_finish+0x6c>
407043b0:	ebffff19 	bl	4070401c <uart_early_puts>
407043b4:	e1a00005 	mov	r0, r5
407043b8:	e28dd008 	add	sp, sp, #8
407043bc:	e8bd8070 	pop	{r4, r5, r6, pc}
407043c0:	e58d6004 	str	r6, [sp, #4]
407043c4:	e59d3004 	ldr	r3, [sp, #4]
407043c8:	e3530063 	cmp	r3, #99	; 0x63
407043cc:	9a000002 	bls	407043dc <hw_dec_wait_finish+0x54>
407043d0:	e3750001 	cmn	r5, #1
407043d4:	0affffee 	beq	40704394 <hw_dec_wait_finish+0xc>
407043d8:	eafffff5 	b	407043b4 <hw_dec_wait_finish+0x2c>
407043dc:	e320f000 	nop	{0}
407043e0:	e59d3004 	ldr	r3, [sp, #4]
407043e4:	e2833001 	add	r3, r3, #1
407043e8:	e58d3004 	str	r3, [sp, #4]
407043ec:	eafffff4 	b	407043c4 <hw_dec_wait_finish+0x3c>
407043f0:	001e8481 	.word	0x001e8481
407043f4:	4073b154 	.word	0x4073b154

407043f8 <hw_dec_decompress>:
407043f8:	e92d40f0 	push	{r4, r5, r6, r7, lr}
407043fc:	e1a06000 	mov	r6, r0
40704400:	e24dd014 	sub	sp, sp, #20
40704404:	e3a00001 	mov	r0, #1
40704408:	e1a04001 	mov	r4, r1
4070440c:	e1a05002 	mov	r5, r2
40704410:	e1a07003 	mov	r7, r3
40704414:	ebffff6e 	bl	407041d4 <hw_dec_sop_eop_first_set>
40704418:	e59f304c 	ldr	r3, [pc, #76]	; 4070446c <hw_dec_decompress+0x74>
4070441c:	e1a01006 	mov	r1, r6
40704420:	e1a00005 	mov	r0, r5
40704424:	e3a02001 	mov	r2, #1
40704428:	e5933000 	ldr	r3, [r3]
4070442c:	e58d3008 	str	r3, [sp, #8]
40704430:	e3a03000 	mov	r3, #0
40704434:	e88d000c 	stm	sp, {r2, r3}
40704438:	e1a02007 	mov	r2, r7
4070443c:	e5943000 	ldr	r3, [r4]
40704440:	ebffffa2 	bl	407042d0 <hw_dec_start>
40704444:	ebffffcf 	bl	40704388 <hw_dec_wait_finish>
40704448:	e59f3020 	ldr	r3, [pc, #32]	; 40704470 <hw_dec_decompress+0x78>
4070444c:	e5933088 	ldr	r3, [r3, #136]	; 0x88
40704450:	f57ff05f 	dmb	sy
40704454:	e2900000 	adds	r0, r0, #0
40704458:	e5843000 	str	r3, [r4]
4070445c:	13a00001 	movne	r0, #1
40704460:	e2600000 	rsb	r0, r0, #0
40704464:	e28dd014 	add	sp, sp, #20
40704468:	e8bd80f0 	pop	{r4, r5, r6, r7, pc}
4070446c:	4073b1d4 	.word	0x4073b1d4
40704470:	11312000 	.word	0x11312000

40704474 <hw_dec_init>:
40704474:	e59f2054 	ldr	r2, [pc, #84]	; 407044d0 <hw_dec_init+0x5c>
40704478:	e5923190 	ldr	r3, [r2, #400]	; 0x190
4070447c:	f57ff05f 	dmb	sy
40704480:	e3833001 	orr	r3, r3, #1
40704484:	f57ff05f 	dmb	sy
40704488:	e5823190 	str	r3, [r2, #400]	; 0x190
4070448c:	f57ff05f 	dmb	sy
40704490:	e59f303c 	ldr	r3, [pc, #60]	; 407044d4 <hw_dec_init+0x60>
40704494:	e3a01000 	mov	r1, #0
40704498:	e5831108 	str	r1, [r3, #264]	; 0x108
4070449c:	f57ff05f 	dmb	sy
407044a0:	e3a02003 	mov	r2, #3
407044a4:	e583210c 	str	r2, [r3, #268]	; 0x10c
407044a8:	f57ff05f 	dmb	sy
407044ac:	e5831110 	str	r1, [r3, #272]	; 0x110
407044b0:	f57ff05f 	dmb	sy
407044b4:	e5832114 	str	r2, [r3, #276]	; 0x114
407044b8:	f57ff05f 	dmb	sy
407044bc:	e5832128 	str	r2, [r3, #296]	; 0x128
407044c0:	f57ff05f 	dmb	sy
407044c4:	e3a02001 	mov	r2, #1
407044c8:	e5832100 	str	r2, [r3, #256]	; 0x100
407044cc:	e12fff1e 	bx	lr
407044d0:	12010000 	.word	0x12010000
407044d4:	11310000 	.word	0x11310000

407044d8 <hw_dec_uinit>:
407044d8:	f57ff05f 	dmb	sy
407044dc:	e59f1034 	ldr	r1, [pc, #52]	; 40704518 <hw_dec_uinit+0x40>
407044e0:	e3a02000 	mov	r2, #0
407044e4:	e1a03002 	mov	r3, r2
407044e8:	e7c03012 	bfi	r3, r2, #0, #1
407044ec:	e7c13092 	bfi	r3, r2, #1, #1
407044f0:	e5812100 	str	r2, [r1, #256]	; 0x100
407044f4:	f57ff05f 	dmb	sy
407044f8:	e59f201c 	ldr	r2, [pc, #28]	; 4070451c <hw_dec_uinit+0x44>
407044fc:	e5813128 	str	r3, [r1, #296]	; 0x128
40704500:	e5923190 	ldr	r3, [r2, #400]	; 0x190
40704504:	f57ff05f 	dmb	sy
40704508:	e3c33001 	bic	r3, r3, #1
4070450c:	f57ff05f 	dmb	sy
40704510:	e5823190 	str	r3, [r2, #400]	; 0x190
40704514:	e12fff1e 	bx	lr
40704518:	11310000 	.word	0x11310000
4070451c:	12010000 	.word	0x12010000

40704520 <start_armboot>:
40704520:	e92d4030 	push	{r4, r5, lr}
40704524:	e24dd014 	sub	sp, sp, #20
40704528:	ebfffeae 	bl	40703fe8 <uart_early_init>
4070452c:	e59f008c 	ldr	r0, [pc, #140]	; 407045c0 <start_armboot+0xa0>
40704530:	ebfffeb9 	bl	4070401c <uart_early_puts>
40704534:	e59f3088 	ldr	r3, [pc, #136]	; 407045c4 <start_armboot+0xa4>
40704538:	e3a00000 	mov	r0, #0
4070453c:	e59f4084 	ldr	r4, [pc, #132]	; 407045c8 <start_armboot+0xa8>
40704540:	e5830000 	str	r0, [r3]
40704544:	ebffffca 	bl	40704474 <hw_dec_init>
40704548:	e59f307c 	ldr	r3, [pc, #124]	; 407045cc <start_armboot+0xac>
4070454c:	e28d100c 	add	r1, sp, #12
40704550:	e5532004 	ldrb	r2, [r3, #-4]
40704554:	e5cd200c 	strb	r2, [sp, #12]
40704558:	e5532003 	ldrb	r2, [r3, #-3]
4070455c:	e5cd200d 	strb	r2, [sp, #13]
40704560:	e5532002 	ldrb	r2, [r3, #-2]
40704564:	e5cd200e 	strb	r2, [sp, #14]
40704568:	e5532001 	ldrb	r2, [r3, #-1]
4070456c:	e5cd200f 	strb	r2, [sp, #15]
40704570:	e59f2058 	ldr	r2, [pc, #88]	; 407045d0 <start_armboot+0xb0>
40704574:	e0433002 	sub	r3, r3, r2
40704578:	e58d0000 	str	r0, [sp]
4070457c:	e1a00004 	mov	r0, r4
40704580:	ebffff9c 	bl	407043f8 <hw_dec_decompress>
40704584:	e2505000 	subs	r5, r0, #0
40704588:	1a000009 	bne	407045b4 <start_armboot+0x94>
4070458c:	e59f0040 	ldr	r0, [pc, #64]	; 407045d4 <start_armboot+0xb4>
40704590:	ebfffea1 	bl	4070401c <uart_early_puts>
40704594:	ebffffcf 	bl	407044d8 <hw_dec_uinit>
40704598:	ee075f15 	mcr	15, 0, r5, cr7, cr5, {0}
4070459c:	ee075fd5 	mcr	15, 0, r5, cr7, cr5, {6}
407045a0:	f57ff04f 	dsb	sy
407045a4:	f57ff06f 	isb	sy
407045a8:	e12fff34 	blx	r4
407045ac:	e28dd014 	add	sp, sp, #20
407045b0:	e8bd8030 	pop	{r4, r5, pc}
407045b4:	e59f001c 	ldr	r0, [pc, #28]	; 407045d8 <start_armboot+0xb8>
407045b8:	ebfffe97 	bl	4070401c <uart_early_puts>
407045bc:	eafffffe 	b	407045bc <start_armboot+0x9c>
407045c0:	4073b173 	.word	0x4073b173
407045c4:	4073b1d4 	.word	0x4073b1d4
407045c8:	40800000 	.word	0x40800000
407045cc:	4073b0c0 	.word	0x4073b0c0
407045d0:	40704750 	.word	0x40704750
407045d4:	4073b181 	.word	0x4073b181
407045d8:	4073b185 	.word	0x4073b185

407045dc <hang>:
407045dc:	e92d4010 	push	{r4, lr}
407045e0:	e59f0004 	ldr	r0, [pc, #4]	; 407045ec <hang+0x10>
407045e4:	ebfffe8c 	bl	4070401c <uart_early_puts>
407045e8:	eafffffe 	b	407045e8 <hang+0xc>
407045ec:	4073b12a 	.word	0x4073b12a

407045f0 <do_bad_sync>:
407045f0:	e92d4010 	push	{r4, lr}
407045f4:	e59f0014 	ldr	r0, [pc, #20]	; 40704610 <do_bad_sync+0x20>
407045f8:	ebfffe87 	bl	4070401c <uart_early_puts>
407045fc:	e59f0010 	ldr	r0, [pc, #16]	; 40704614 <do_bad_sync+0x24>
40704600:	ebfffe85 	bl	4070401c <uart_early_puts>
40704604:	e3a00000 	mov	r0, #0
40704608:	e8bd4010 	pop	{r4, lr}
4070460c:	ea000047 	b	40704730 <reset_cpu>
40704610:	4073b105 	.word	0x4073b105
40704614:	4073b116 	.word	0x4073b116

40704618 <do_sync>:
40704618:	e92d4010 	push	{r4, lr}
4070461c:	e59f0014 	ldr	r0, [pc, #20]	; 40704638 <do_sync+0x20>
40704620:	ebfffe7d 	bl	4070401c <uart_early_puts>
40704624:	e59f0010 	ldr	r0, [pc, #16]	; 4070463c <do_sync+0x24>
40704628:	ebfffe7b 	bl	4070401c <uart_early_puts>
4070462c:	e3a00000 	mov	r0, #0
40704630:	e8bd4010 	pop	{r4, lr}
40704634:	ea00003d 	b	40704730 <reset_cpu>
40704638:	4073b109 	.word	0x4073b109
4070463c:	4073b116 	.word	0x4073b116

40704640 <do_bad_error>:
40704640:	e92d4010 	push	{r4, lr}
40704644:	e59f0014 	ldr	r0, [pc, #20]	; 40704660 <do_bad_error+0x20>
40704648:	ebfffe73 	bl	4070401c <uart_early_puts>
4070464c:	e59f0010 	ldr	r0, [pc, #16]	; 40704664 <do_bad_error+0x24>
40704650:	ebfffe71 	bl	4070401c <uart_early_puts>
40704654:	e3a00000 	mov	r0, #0
40704658:	e8bd4010 	pop	{r4, lr}
4070465c:	ea000033 	b	40704730 <reset_cpu>
40704660:	4073b0c4 	.word	0x4073b0c4
40704664:	4073b116 	.word	0x4073b116

40704668 <do_error>:
40704668:	e92d4010 	push	{r4, lr}
4070466c:	e59f0014 	ldr	r0, [pc, #20]	; 40704688 <do_error+0x20>
40704670:	ebfffe69 	bl	4070401c <uart_early_puts>
40704674:	e59f0010 	ldr	r0, [pc, #16]	; 4070468c <do_error+0x24>
40704678:	ebfffe67 	bl	4070401c <uart_early_puts>
4070467c:	e3a00000 	mov	r0, #0
40704680:	e8bd4010 	pop	{r4, lr}
40704684:	ea000029 	b	40704730 <reset_cpu>
40704688:	4073b0c8 	.word	0x4073b0c8
4070468c:	4073b116 	.word	0x4073b116

40704690 <do_bad_fiq>:
40704690:	e92d4010 	push	{r4, lr}
40704694:	e59f0014 	ldr	r0, [pc, #20]	; 407046b0 <do_bad_fiq+0x20>
40704698:	ebfffe5f 	bl	4070401c <uart_early_puts>
4070469c:	e59f0010 	ldr	r0, [pc, #16]	; 407046b4 <do_bad_fiq+0x24>
407046a0:	ebfffe5d 	bl	4070401c <uart_early_puts>
407046a4:	e3a00000 	mov	r0, #0
407046a8:	e8bd4010 	pop	{r4, lr}
407046ac:	ea00001f 	b	40704730 <reset_cpu>
407046b0:	4073b0d0 	.word	0x4073b0d0
407046b4:	4073b116 	.word	0x4073b116

407046b8 <do_bad_irq>:
407046b8:	e92d4010 	push	{r4, lr}
407046bc:	e59f0014 	ldr	r0, [pc, #20]	; 407046d8 <do_bad_irq+0x20>
407046c0:	ebfffe55 	bl	4070401c <uart_early_puts>
407046c4:	e59f0010 	ldr	r0, [pc, #16]	; 407046dc <do_bad_irq+0x24>
407046c8:	ebfffe53 	bl	4070401c <uart_early_puts>
407046cc:	e3a00000 	mov	r0, #0
407046d0:	e8bd4010 	pop	{r4, lr}
407046d4:	ea000015 	b	40704730 <reset_cpu>
407046d8:	4073b0ed 	.word	0x4073b0ed
407046dc:	4073b116 	.word	0x4073b116

407046e0 <do_fiq>:
407046e0:	e92d4010 	push	{r4, lr}
407046e4:	e59f0014 	ldr	r0, [pc, #20]	; 40704700 <do_fiq+0x20>
407046e8:	ebfffe4b 	bl	4070401c <uart_early_puts>
407046ec:	e59f0010 	ldr	r0, [pc, #16]	; 40704704 <do_fiq+0x24>
407046f0:	ebfffe49 	bl	4070401c <uart_early_puts>
407046f4:	e3a00000 	mov	r0, #0
407046f8:	e8bd4010 	pop	{r4, lr}
407046fc:	ea00000b 	b	40704730 <reset_cpu>
40704700:	4073b0d4 	.word	0x4073b0d4
40704704:	4073b116 	.word	0x4073b116

40704708 <do_irq>:
40704708:	e92d4010 	push	{r4, lr}
4070470c:	e59f0014 	ldr	r0, [pc, #20]	; 40704728 <do_irq+0x20>
40704710:	ebfffe41 	bl	4070401c <uart_early_puts>
40704714:	e59f0010 	ldr	r0, [pc, #16]	; 4070472c <do_irq+0x24>
40704718:	ebfffe3f 	bl	4070401c <uart_early_puts>
4070471c:	e3a00000 	mov	r0, #0
40704720:	e8bd4010 	pop	{r4, lr}
40704724:	ea000001 	b	40704730 <reset_cpu>
40704728:	4073b0f1 	.word	0x4073b0f1
4070472c:	4073b116 	.word	0x4073b116

40704730 <reset_cpu>:
40704730:	e59f100c 	ldr	r1, [pc, #12]	; 40704744 <rstctl>
40704734:	e3a03002 	mov	r3, #2
40704738:	e5813000 	str	r3, [r1]
4070473c:	e1a00000 	nop			; (mov r0, r0)

40704740 <_loop_forever>:
40704740:	eafffffe 	b	40704740 <_loop_forever>

40704744 <rstctl>:
40704744:	12020004 	.word	0x12020004
