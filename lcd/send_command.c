#include "lcd.h"

/*
 * Various LCD commands.
 */

/*
 * Send a geric command to the LCD, weather it be to the control
 * register or to the data register.
 */
void _lcd_send_command(enum reg_type type,
                       unsigned char data)
{
	ioreg new_pio_b = readw(PIO_B);

	// Ensure the LCD isn't busy.
	_lcd_busy();

	// get the pio.

	if(type == REG_DATA)
		new_pio_b |= LCD_RS;
	else
		new_pio_b &= ~LCD_RS;

	// We want to write ane ensure the LCD is diabled.
	// Also ensure that LEDs are disabled.
	new_pio_b &= ~(LCD_RW | LCD_E | LED_ENABLE);

	// write the new PIO_B.
	writew(new_pio_b, PIO_B);

	// write the data to PIO A.
	writew(data, PIO_A);

	// Enable the LCD.
	new_pio_b |= LCD_E;
	writew(new_pio_b, PIO_B);

	// disable the LCD.
	new_pio_b &= ~LCD_E;
	writew(new_pio_b, PIO_B);
}


/*
 * Set the backlight state.
 *
 * state != 0; Enable the backlight.
 * state = 0; disable the backlight.
 */
void _lcd_backlight_control(unsigned char state)
{
	ioreg new_pio_b = readw(PIO_B);
	if(state)
		new_pio_b |= LCD_BACKLIGHT_MASK;
	else
		new_pio_b &= ~LCD_BACKLIGHT_MASK;
	writew(new_pio_b, PIO_B);
}
