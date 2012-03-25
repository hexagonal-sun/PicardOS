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
	/* Initialise memory */
	MOV R0, #0
	LDR R1, =PCB_HEAD
	STR R0, [R1]
	LDR R1, =SHOULD_CTX_SWITCH
	STR R0, [R1]

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

	/* Switch back to sup mode for program
	   initalisation */
	MSR CPSR_c, #CPSR_SUP

	/* Fork to the user program */
	LDR R0, =proc1
	MOV R1, #1000
	BL  _fork
	LDR R0, =proc2
	MOV R1, #1000
	BL  _fork
	LDR R0, =main
	MOV R1, #100
	BL _fork

	B  _task_switch
