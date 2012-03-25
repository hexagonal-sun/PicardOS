#include "../lcd/lcd.h"

void _print_string(const char* c)
{
  int i = 0;
  char temp = c[i];
  while(temp != 0)
    {
      _print_char(temp);
      i++;
      temp = c[i];
    }
}

void print_string(const char* c)
{
  __asm__ volatile("svc 6");
}
