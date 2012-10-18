
/*
 * Framework for allowing functions to register setup calls for kernel
 * boot.
 */

extern unsigned int _early_initcall_begin;
extern unsigned int _early_initcall_end;
extern unsigned int _initcall_begin;
extern unsigned int _initcall_end;

typedef void (*initcall_fn)(void);

#define __def_initcall(fn,lvl) initcall_fn __initcall_##fn##lvl \
	__attribute__((section(".initcall" #lvl))) = fn

#define early_initcall(fn) __def_initcall(fn,0)
#define initcall(fn) __def_initcall(fn,1)

void init();
