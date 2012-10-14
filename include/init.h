
/*
 * Framework for allowing functions to register setup calls for kernel
 * boot.
 */

extern unsigned int _initcall_begin;
extern unsigned int _initcall_end;

typedef void (*initcall_fn)(void);

#define init_call(fn) initcall_fn __initcall_##fn	\
	__attribute__((section(".initcall"))) = fn

void init();
