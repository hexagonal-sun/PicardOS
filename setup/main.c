#include <init.h>

void main()
{
	initcall_fn current_call = (initcall_fn)_initcall_begin;
	initcall_fn last_call = (initcall_fn)_initcall_end;

	// Call all inits.
	while (current_call != last_call)
	{
		current_call();
		current_call++;
	}
}
