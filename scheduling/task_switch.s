	.global _task_switch

_armv7_idle:
	WFI

_task_switch:

	/* reset the context_swtich flag. */
	LDR R0, =SHOULD_CTX_SWITCH
	MOV R1, #0
	STR R1, [R0]

	/* Load the tasks cpsr into the spsr */
	LDR R0, =PCB_HEAD
	LDR R0, [R0]

	CMP R0, #0
	BEQ _armv7_idle

	LDR R1, [R0, #(15 * 4)]
	MSR spsr, R1

	/* Get the tasks' pc */
	LDR LR, [R0, #(16 * 4)]

	/* Load in the registers */
	LDM R0, {R0-R14}^

	/* Branch to the user's code. */
	MOVS PC, LR


