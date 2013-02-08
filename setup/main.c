#include <init.h>
#include <up.h>
#include <ksyscalls.h>
#include <sched.h>
#include <print.h>

void copy_vectors()
{
	extern unsigned int _vec_start;
	extern unsigned int _vec_end;
	volatile unsigned int *current_vec = (unsigned int *)&_vec_start;
	volatile unsigned int *end_vec = (unsigned int *)&_vec_end;
	volatile unsigned int *dest_vec = (unsigned int *)0x0;
	while (current_vec != end_vec) {
		*(dest_vec) = *(current_vec);
		dest_vec++;
		current_vec++;
	}
}
early_initcall(copy_vectors);

void call_initcalls(unsigned int *begin,
		    unsigned int *end)
{
	initcall_fn *current_call = (initcall_fn*)begin;
	while (current_call != (initcall_fn*)end) {
		(*current_call)();
		current_call++;
	}
}

void main()
{
	call_initcalls(&_system_initcall_begin,
		       &_system_initcall_end);

	call_initcalls(&_early_initcall_begin,
		       &_early_initcall_end);

	print_str("PicardOS v0.1 booting...\n");

	call_initcalls(&_initcall_begin,
		       &_initcall_end);

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
