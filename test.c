#include <up.h>
#include <syscalls.h>

void delay()
{
  for(volatile int i = 0; i < 1000; i++)
    {
	
    }
}

int proc1()
{
  while(1)
    {
      write_pio_a(24);
    }
}
user_process(proc1,1000);

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

void lcd_test()
{
  while(1)
    {
      lcd_send_command(BACKLIGHT_ON);
      delay();
      lcd_send_command(BACKLIGHT_OFF);
      delay();
    }
}

void lcd_print_test()
{
  char* c = "Hello, World!\nAlso, Hi!";
  lcd_send_command(BACKLIGHT_ON);
  print_string(c);
  volatile int i = 0;
  while(1)
    {
      i++;
    }
}
