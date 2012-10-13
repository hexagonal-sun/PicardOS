/*
 * A framework for declaring user processes for the kernel to
 * start
 */

extern unsigned int _up_begin;
extern unsigned int _up_end;

typedef int (*up_fn)(void);

typedef struct
{
	up_fn u_fn;
	unsigned int s_size;
}up;

#define user_process(fn,stack_size) up __up_##fn      \
	__attribute__((section(".user_processes"))) = \
	{.u_fn = fn,.s_size = stack_size}
