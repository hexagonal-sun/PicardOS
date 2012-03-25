#include "syscalls.h"

void lcd_send_command(enum lcd_command command)
{
	switch(command)
	{
		case CLEAR_AND_RESET:
			__asm__ volatile("mov R0, #1\n" /* set the control register */
			                 "mov R1, #1\n" /* set the clear command */
			                 "svc 7" ::: "r0", "r1");
			break;
		case BACKLIGHT_ON:
			__asm__ volatile("mov R0, #1\n"
			                 "svc 5" ::: "r0");
			break;
		case BACKLIGHT_OFF:
			__asm__ volatile("mov R0, #0\n"
			                 "svc 5" ::: "r0");
			break;
	}
}
