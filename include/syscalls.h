enum lcd_command
{
	CLEAR_AND_RESET, /* Clear the screen and reset the cursor to home */
	BACKLIGHT_ON,
	BACKLIGHT_OFF
};

void halt(); /* svc 0 */
unsigned int get_timer_val(); /* svc 1 */
void write_pio_a(unsigned int val); /* svc 2*/
void fork(unsigned int start_address,
	  unsigned int stack_size); /* svc 3*/
void exit(); /* svc 4 */
/* svc 5 - reserved. */
void print_string(const char* c); /* svc 6 */
void lcd_send_command(enum lcd_command command); /* svc 7 */
