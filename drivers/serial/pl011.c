#include <serial.h>
#include <io.h>
#include <init.h>

#define PL011_BASE 0x10009000
#define OE_MASK 0x00000800

void pl011_write_char(char c)
{
	volatile iomem UARTDR = __io_address(PL011_BASE);
	volatile unsigned int state;
	while (1) {
		state = readw(UARTDR);
		state &= OE_MASK;
		if (!state)
			break;
	}
	writeb(c, UARTDR);
}

struct serial_device pl011_dev = {
	.write_char = pl011_write_char
};

void pl011_init()
{
	active_console = &pl011_dev;
}
early_initcall(pl011_init);
