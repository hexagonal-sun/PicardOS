#include "syscalls.h"

volatile unsigned int* pio_b = (unsigned int*)0x10000004;
const unsigned int backlight_enable_mask = 0x20;

void _lcd_ctl(unsigned char command)
{
  switch(command)
    {
    case BACKLIGHT_ON: /* toggle backlight */
      (*pio_b) |= backlight_enable_mask;
      break;
    case BACKLIGHT_OFF:
      (*pio_b) &= ~backlight_enable_mask;
      break;
    }
}

void lcd_ctl(unsigned char command)
{
  __asm__ volatile("svc 5");
}
