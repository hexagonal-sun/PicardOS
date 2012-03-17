	.set CPSR_USER, 0x10
	.set CPSR_SYS, 0x1F
	.set CPSR_SUP, 0x13
	.set CPSR_IRQ, 0x12
	.set IRQ_ENABLE, 0x1000001C
	.global _start
_start:
	b setup
	b _exit
	b __syscall
	b _exit
	b _exit
	b _exit
	b __irq_entry
	b _exit
	b _exit
	b _exit
	b _exit
	b _exit
	b _exit
	b _exit
	b _exit

setup:
	/* set the supervisor stack */
	LDR sp,=0x00037C00
	BL  _timer_setup

	/* Switch to IRQ Mode */
	MSR CPSR_c, #CPSR_IRQ

	/* Set the IRQ stack */
	LDR sp,=0x00047C00

	/* Enable interupts */
	MOV R0, #1
	LDR R1, =IRQ_ENABLE
	STR R0, [R1]

	/* Switch to System mode. */
	MSR CPSR_c, #CPSR_SYS
	ldr sp,=0x00027C00

	/* Switch to User mode */
	MSR CPSR_c, #CPSR_USER

	/* Execute the user programs */
	bl main

	/* System halt. */
	svc 0
