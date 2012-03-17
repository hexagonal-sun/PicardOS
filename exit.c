#include "syscalls/syscalls.h"
void _exit()
{
	halt();
}
