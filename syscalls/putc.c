#include <serial.h>

void _putc(char c)
{
	if (active_console)
		active_console->write_char(c);
}

void putc(char c)
{
	__asm__ volatile("svc 3");
}
