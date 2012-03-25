#include "syscalls/syscalls.h"

void delay()
{
  for(volatile int i = 0; i < 1000; i++)
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
  for(int i =0; i < 10000; i++)
    {
      write_pio_a(temp);
    }

}


void lcd_test()
{
  while(1)
    {
      lcd_ctl(BACKLIGHT_ON);
      delay();
      lcd_ctl(BACKLIGHT_OFF);
      delay();
    }
}

void lcd_print_test()
{
  char* c = "Hello, World!\nAlso, Hi!";
  lcd_ctl(BACKLIGHT_ON);
  print_string(c);
  volatile int i = 0;
  while(1)
    {
      i++;
    }
}
