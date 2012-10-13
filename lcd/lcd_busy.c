#include "lcd.h"

volatile unsigned int* PIO_A = (unsigned int*)0x10000000;
volatile unsigned int* PIO_B = (unsigned int*)0x10000004;

void _lcd_busy()
{
  unsigned int lcd_state = 0;

  do
    {
      // Set pio_b to read the state.
      unsigned int new_pio_b = (*PIO_B);
      new_pio_b &= ~(LED_ENABLE | LCD_E | LCD_RS);
      new_pio_b |= (LCD_RW);
      (*PIO_B) = new_pio_b;

      // Enaable the lcd.
      new_pio_b |= LCD_E;
      (*PIO_B) = new_pio_b;

      // read port a
      lcd_state = (*PIO_A);

      // Disable the lcd.
      new_pio_b &= ~LCD_E;
      (*PIO_B) = new_pio_b;

      // check the flag.
    }while(lcd_state & LCD_BUSY_MASK);
}
