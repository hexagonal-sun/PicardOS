#include <io.h>
#include "lcd.h"

void _lcd_busy()
{
  ioreg lcd_state = 0;
  ioreg new_pio_b = readw(PIO_B);

  do
    {
      // Set pio_b to read the state.
      new_pio_b &= ~(LED_ENABLE | LCD_E | LCD_RS);
      new_pio_b |= (LCD_RW);
      writew(new_pio_b, PIO_B);

      // Enaable the lcd.
      new_pio_b |= LCD_E;
      writew(new_pio_b, PIO_B);

      // read port a
      lcd_state = readw(PIO_A);

      // Disable the lcd.
      new_pio_b &= ~LCD_E;
      writew(new_pio_b, PIO_B);

      // check the flag.
    }while(lcd_state & LCD_BUSY_MASK);
}
