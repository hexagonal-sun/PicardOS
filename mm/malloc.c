#include <mm.h>
#include <init.h>

char *malloc_ptr;

void mem_init()
{
	malloc_ptr = (char *)data_start;
}
system_initcall(mem_init);

void *malloc(unsigned int sz)
{
	char *return_address = malloc_ptr;
	malloc_ptr += sz;
	return (void*)return_address;
}
