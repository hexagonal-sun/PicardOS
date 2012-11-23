	.set CPSR_USER, 0x10
	.set CPSR_SYS, 0x1F
	.set CPSR_SUP, 0x13
	.set CPSR_IRQ, 0x12
	.set IRQ_ENABLE, 0x1000001C
	.global _vec_start
	.global _vec_end
_start:
	mov r12, pc
_vec_start:
	LDR pc, [pc, #24]
	LDR pc, [pc, #24]
	LDR pc, [pc, #24]
	LDR pc, [pc, #24]
	LDR pc, [pc, #24]
	LDR pc, [pc, #24]
	LDR pc, [pc, #24]
	LDR pc, [pc, #24]
	.word    __setup                 @ reset
	.word    .                       @ undef
	.word    __syscall               @ svc
	.word    .                       @ pabort
	.word    .                       @ dabort
	.word    .                       @ hyp
	.word    __irq_entry             @ irq
	.word    .                       @ fiq

_vec_end:
	.align 8

__setup:
	/* Initialise memory */
	MOV R0, #0
	LDR R1, =PCB_HEAD
	STR R0, [R1]
	LDR R1, =SHOULD_CTX_SWITCH
	STR R0, [R1]

	/* set the supervisor stack */
	LDR sp, =svc_stack_end

	/* Switch to IRQ Mode */
	MSR CPSR_c, #CPSR_IRQ

	/* Set the IRQ stack */
	LDR sp, =irq_stack_end

	/* Enable interupts */
	MOV R0, #1
	LDR R1, =IRQ_ENABLE
	STR R0, [R1]

	/* Switch back to sup mode for kernel
	   initalisation */
	MSR CPSR_c, #CPSR_SUP

	LDR R0, =main
	mov PC, R0

	B  .	@We should never get here.
	.section ".stack"
svc_stack_begin:	.space	4096
svc_stack_end:		.space 4096
irq_stack_end:
