#include <up.h>
#include <syscalls.h>

void delay()
{
  for(volatile int i = 0; i < 1000; i++)
    {
	
    }
}


int factorial(int num)
{
	if(num == 0)
		return 1;
	return (num * factorial(num - 1));
}

int serial_hello()
{
	char *c = "Hello from user space!\n";
	char cc = *c;
	while (cc != '\0') {
		putc(cc); 
		cc = *c++;
	}
	return 0;
}
user_process(serial_hello,1000);
