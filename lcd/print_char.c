#include "../misc/addresses.h"
#include "lcd.h"

void _print_char(unsigned char c)
{
  // check for newline.
  if(c == '\n')
  {
	  // set the newline on the display.
	  _lcd_send_command(REG_CONTROL, LCD_NEWLINE);
  }
  else
  {
	  // print the char.
	  _lcd_send_command(REG_DATA, c);
  }
}
