void halt(); /* svc 0 */
unsigned int get_timer_val(); /* svc 1 */
void write_pio_a(unsigned int val); /* svc 2*/
void fork(unsigned int start_address,
	  unsigned int stack_size); /* svc 3*/

