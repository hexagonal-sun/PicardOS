.global			__syscall
.set svc_opcode_clear,	0xFF000000
.set max_swi,		0x03

__syscall:		PUSH {R12, LR}

			/* Calulate and mask off the opcode. */
			LDR  R12, [LR, #-4]
			BIC  R12, R12, #svc_opcode_clear

			/* Ensure a correct SWI number */
			CMP  R12, #max_swi
			BHI  svc_return

			/* Load the return address */
			ADR LR, svc_return

			/* Check if this is an exit routine. */
			CMP R12, #2

			/* Load the return if we are an exit call. */
			ADREQ LR, svc_exit_return

			/* Do the jump */
			ADD  R12, PC, R12, LSL #2  /* Calc table offset. */
			LDR  PC, [R12, #0] /* Load into the PC. */

jump_table:		.word _halt
			.word _fork
			.word _exit
			.word _putc

svc_return:		POP  {R12, LR}
			MOVS PC, LR

svc_exit_return:	POP {R12, LR}
			B _task_switch
