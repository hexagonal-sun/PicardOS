.global			__syscall
.set svc_opcode_clear,	0xFF000000
.set max_swi,		0x04

__syscall:		PUSH {R12, LR}

			/* Calulate and mask off the opcode. */
			LDR  R12, [LR, #-4]
			BIC  R12, R12, #svc_opcode_clear

			/* Ensure a correct SWI number */
			CMP  R12, #max_swi
			BHI  svc_return

			/* Load the return address. */
			ADR  LR, svc_return

			/* Do the jump */
			ADD  R12, PC, R12, LSL #2  /* Calc table offset. */
			LDR  PC, [R12, #0] /* Load into the PC. */

jump_table:	.word _write_pio_a

svc_return:	POP  {R12, LR}
	        MOVS PC, LR
	
