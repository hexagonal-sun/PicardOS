	.global __irq_entry
	.set port_area, 0x10000000
	.set irq_ack, 0x18
	.set irq_timer, 0x01

__irq_entry:
	SUB  LR, LR, #4 /*Set the correct return address. */
	PUSH {LR}       /*Store the address and scratch registers.*/
	PUSH {R0-R6}
	MOV  R3, #port_area /*set the I/O port address.*/
	LDR  R0, [R3, #irq_ack] /*find which interrupt was called*/
	TST  R0, #irq_timer     /*Timer interrupt.*/
	BLNE _irq_timer_handle
	STR  R0, [R3, #irq_ack] /*Acknowledge the interrupt.*/
	POP  {R0-R6}
	POP  {LR}
	MOVS PC, LR

