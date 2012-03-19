	.global __irq_entry
	.set port_area, 0x10000000
	.set irq_ack, 0x18
	.set mode_mask, 0x000000FF
	.set mode_user, 0x10
	.set irq_timer, 0x01

__irq_entry:
	SUB  LR, LR, #4 /*Set the correct return address. */

	/* Save the scratch registers */
	PUSH {R0-R4, LR}

	MOV  R3, #port_area /*set the I/O port address.*/
	LDR  R0, [R3, #irq_ack] /*find which interrupt was called*/
	TST  R0, #irq_timer     /*Timer interrupt.*/
	BLNE _irq_timer_handle
	STR  R0, [R3, #irq_ack] /*Acknowledge the interrupt.*/

	LDRB R0, =SHOULD_CTX_SWITCH /* Load the context switch flag */
	CMP  R0, #0 /* See if we should switch the context. */
	POPEQ  {R0-R4, PC}^ /* Return back to the calling process. */

	/* Only task switch if we're in user mode, not SVC. */
	MRS R1, SPSR
	AND R0, R1, #mode_mask
	CMP R0, #mode_user
	POPNE {R0-R4, PC}^

	/* Get the current PCB */
	LDR R0, =PCB_HEAD
	LDR R0, [R0]

	/* Store the condition codes */
	MRS R1, SPSR
	STR R1, [R0, #(15 * 4)]

	/* Save R5 - R13 */
	ADD R3, R0, #(5 * 4)
	STM R3, {R5-R14}^

	/* Save r0 - r4 from the stack */
	POP {R5 - R9}
	STM R0, {R5 - R9}

	/* Store the PC */
	POP {R2}
	STR R2, [R0, #(16 * 4)]

	BL _set_next_task
	B _task_switch
