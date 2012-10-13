#include <mm.h>
#include <init.h>

extern unsigned int _edata;
char *malloc_ptr;

void mem_init()
{
	malloc_ptr = (char *)_edata;
}
init_call(mem_init);

void *malloc(unsigned int sz)
{
	char *return_address = malloc_ptr;
	malloc_ptr += sz;
	return (void*)return_address;
}
