	.set CPSR_USER, 0x10
	.set PAGE_MASK, 0xfffff
	.set CPSR_SYS, 0x1F
	.set CPSR_SUP, 0x13
	.set CPSR_IRQ, 0x12
	.set IRQ_ENABLE, 0x1000001C
	.global _vec_start
	.global _vec_end
_start:
	mov	r12, pc		@ Save the start address
	ldr	r0,=PAGE_MASK
	bic	r12, r12, r0		@ Page align the star addr ptr

	adr	sp, __boot_stack	@ Set the boot stack

	mov	r0, r12
	ldr	r1, =0xc0000000	@ Load the linked kernel address
	bl	setup_pg_tables

	mov	r6, r0
	mov	r0, #0
	mcr	p15, 0, r0, c7, c10, 4  @ drain write buffer
	mcr	p15, 0, r0, c8, c7, 0   @ flush I,D TLBs
	mrc	p15, 0, r0, c1, c0, 0   @ read control reg
	bic	r0, r0, #1 << 28        @ clear SCTLR.TRE
	orr	r0, r0, #0x5000         @ I-cache enable, RR cache replacement
	orr	r0, r0, #0x003c         @ write buffer
	orr	r0, r0, #1              @ MMU enabled
	mov	r1, #0xfffffffd         @ domain 0 = client
	bic	r6, r6, #1 << 31        @ 32-bit translation system
	bic	r6, r6, #3 << 0         @ use only ttbr0
	mcr	p15, 0, r3, c2, c0, 0   @ load page table pointer
	mcr	p15, 0, r1, c3, c0, 0   @ load domain access control
	mcr	p15, 0, r6, c2, c0, 2   @ load ttb control
	mcr	p15, 0, r0, c7, c5, 4   @ ISB
	mcr	p15, 0, r0, c1, c0, 0   @ load control register
	mrc	p15, 0, r0, c1, c0, 0   @ and read it back
	mov	r0, #0
	mcr	p15, 0, r0, c7, c5, 4   @ ISB

	mov	r0, r12		@ Load the kernel PA
	ldr	r1, =0xc0000000	@ Set the kernel linked VA
	mov	r2, r6			@ Load the kernel pdp

	ldr	sp, =__boot_stack	@ Set the VA of the temporary stack.
	ldr	r3, =post_mmu_setup	@ Load the VA of the fn
	ldr	lr, =1f			@ Set the virtual return address
	mov	pc, r3			@ Branch to the fn

1:
	mov	sp, r0

	LDR R0, =main			@ Jump to C code.
	mov PC, R0

	b	.			@ We should never get here.
	.ltorg
	.space	512
__boot_stack:
	.section ".vectors"
_vec_start:
	ldr	pc, [pc, #24]
	ldr	pc, [pc, #24]
	ldr	pc, [pc, #24]
	ldr	pc, [pc, #24]
	ldr	pc, [pc, #24]
	ldr	pc, [pc, #24]
	ldr	pc, [pc, #24]
	ldr	pc, [pc, #24]
	.word	.                       @ reset
	.word	.                       @ undef
	.word	__syscall               @ svc
	.word	.                       @ pabort
	.word	.                       @ dabort
	.word	.                       @ hyp
	.word	__irq_entry             @ irq
	.word	.                       @ fiq
_vec_end:
