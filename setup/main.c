#include <init.h>
#include <up.h>
#include <ksyscalls.h>
#include <sched.h>

void main()
{
	/*
	 * Call kernel init calls.
	 */
	initcall_fn *current_call = (initcall_fn*)&_initcall_begin;
	while (current_call != (initcall_fn*)&_initcall_end) {
		(*current_call)();
		current_call++;
	}

	/*
	 * Fork user processes.
	 */
	up *current_up = (up *)&_up_begin;
	while (current_up != (up *)&_up_end) {
		_fork((unsigned int)current_up->u_fn,
		     current_up->s_size);
		current_up++;
	}
	_task_switch();
}
