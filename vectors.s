	.set CPSR_USER, 0x10
	.set CPSR_SYS, 0x1F
	.set CPSR_SUP, 0x13
	.globl _start
_start:
	b setup
	b _exit
	b __syscall
	b _exit
	b _exit
	b _exit
	b _exit
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
	ldr sp,=0x00037C00
	MSR CPSR_c, #CPSR_SYS
	ldr sp,=0x00027C00
	MSR CPSR_c, #CPSR_USER
	bl main
	MSR CPSR_c, #CPSR_SUP
	svc 0
