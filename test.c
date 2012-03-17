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
      write_pio_a(get_timer_val());
      delay();
      write_pio_a(get_timer_val());
      delay();
    }
}
