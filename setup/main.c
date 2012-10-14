#include <init.h>
#include <up.h>
#include <syscalls.h>
#include <sched.h>

void main()
{
	initcall_fn current_call = (initcall_fn)_initcall_begin;
	initcall_fn last_call = (initcall_fn)_initcall_end;

	// Call all inits.
	while (current_call != last_call) {
		current_call();
		current_call++;
	}

	// Fork user processes.
	up *current_up = (up *)_up_begin;
	while (current_up != (up*)_up_end) {
		fork((unsigned int)current_up->u_fn,
		     current_up->s_size);
	}
	_task_switch();
}
