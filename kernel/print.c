#include <serial.h>

void print_str(char *str)
{
	char *ptr = str;
	char c = *ptr;
	while (c != '\0') {
		active_console->write_char(c);
		ptr++;
		c = *ptr;
	}
}
