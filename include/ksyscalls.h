enum lcd_command
{
	CLEAR_AND_RESET, /* Clear the screen and reset the cursor to home */
	BACKLIGHT_ON,
	BACKLIGHT_OFF
};

void _halt(); /* svc 0 */
unsigned int _get_timer_val(); /* svc 1 */
void _write_pio_a(unsigned int val); /* svc 2*/
void _fork(unsigned int start_address,
	  unsigned int stack_size); /* svc 3*/
void _exit(); /* svc 4 */
/* svc 5 - reserved. */
void _print_string(const char* c); /* svc 6 */
void _lcd_send_command(enum lcd_command command); /* svc 7 */
