#include <stdio.h>
#include "syscalls/syscalls.h"

void delay()
{
	for(int i = 0; i < 10000; i++)
{
	
}
}

int main()
{
	for(int i = 0; i < 5; i++)
{
  int* timer = (int*)0x10000008;
write_pio_a(*timer);
	delay();
	write_pio_a(*timer);
	delay();
}	
}
