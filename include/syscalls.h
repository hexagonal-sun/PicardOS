enum lcd_command
{
	CLEAR_AND_RESET, /* Clear the screen and reset the cursor to home */
	BACKLIGHT_ON,
	BACKLIGHT_OFF
};

void halt(); /* svc 0 */
void fork(unsigned int start_address,
	  unsigned int stack_size); /* svc 1*/
void exit(); /* svc 2 */
void putc(char c); /* svc 3 */
