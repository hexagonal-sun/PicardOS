#include "../misc/addresses.h"
#include "lcd.h"

void _print_char(unsigned char c)
{
  // Ensure the lcd isn't busy.
  _lcd_busy();

  // Set to write ‘data’ with data bus direction as output
  unsigned int new_pio_b = (*PIO_B);
  new_pio_b |= LCD_RS;
  new_pio_b &= ~LCD_RW;
  (*PIO_B) = new_pio_b;

  // Write the data byte.
  (*PIO_A) = (unsigned int)c;

  // Enable the LCD.
  (*PIO_B) |= LCD_E;

  // Disable the LCD.
  (*PIO_B) &= ~LCD_E;
}
