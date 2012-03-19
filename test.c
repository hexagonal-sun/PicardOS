#include <stdio.h>
#include "syscalls/syscalls.h"

void delay()
{
  for(int i = 0; i < 10000; i++)
    {
	
    }
}

void proc1()
{
  while(1)
    {
      write_pio_a(24);
    }
}

void proc2()
{
  while(1)
    {
      write_pio_a(10);
    }
}


int factorial(int num)
{
	if(num == 0)
		return 1;
	return (num * factorial(num - 1));
}

int main()
{
	int temp = 0;
  for(int i = 0; i < 5; i++)
    {
      temp += factorial(get_timer_val() % 8);
    }
  while(1)
    {
      write_pio_a(temp);
    }

}
