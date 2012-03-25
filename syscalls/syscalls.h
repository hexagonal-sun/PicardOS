void halt(); /* svc 0 */
unsigned int get_timer_val(); /* svc 1 */
void write_pio_a(unsigned int val); /* svc 2*/
void fork(unsigned int start_address,
	  unsigned int stack_size); /* svc 3*/
void exit(); /* svc 4 */
void lcd_ctl(unsigned char command); /* svc 5 */
void print_string(const char* c); /* svc 6 */


/**
 * lcd_ctl commands
 */

#define BACKLIGHT_ON 0
#define BACKLIGHT_OFF 1
