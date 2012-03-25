#include "lcd.h"
#include "../misc/addresses.h"

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
	// Ensure the LCD isn't busy.
	_lcd_busy();

	// get the pio.
	unsigned int new_pio_b = (*PIO_B);

	if(type == REG_DATA)
		new_pio_b |= LCD_RS;
	else
		new_pio_b &= ~LCD_RS;

	// We want to write ane ensure the LCD is diabled.
	// Also ensure that LEDs are disabled.
	new_pio_b &= ~(LCD_RW | LCD_E | LED_ENABLE);

	// write the new PIO_B.
	(*PIO_B) = new_pio_b;

	// write the data to PIO A.
	(*PIO_A) = data;

	// Enable the LCD.
	new_pio_b |= LCD_E;
	(*PIO_B) = new_pio_b;

	// disable the LCD.
	new_pio_b &= ~LCD_E;
	(*PIO_B) = new_pio_b;
}


/*
 * Set the backlight state.
 *
 * state != 0; Enable the backlight.
 * state = 0; disable the backlight.
 */
void _lcd_backlight_control(unsigned char state)
{
	unsigned int new_pio_b = (*PIO_B);
	if(state)
		new_pio_b |= LCD_BACKLIGHT_MASK;
	else
		new_pio_b &= ~LCD_BACKLIGHT_MASK;
	(*PIO_B) = new_pio_b;
}
