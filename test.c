#include <stdio.h>

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
  int* port = (int*)0x10000000;
  int* timer = (int*)0x10000008;
	*port = (*timer);
	delay();
	*port = (*timer);
	delay();
}	
}
