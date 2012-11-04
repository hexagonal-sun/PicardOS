#include <io.h>

void writeb(char val, iomem addr)
{
	__asm volatile ("strb %[val], [ %[address] ]"
			:
			: [address]"r" (addr), [val]"r" (val)
			: );
}


void writew( unsigned int val, iomem addr)
{
	__asm volatile("str %[val], [ %[address] ]"
		       :
		       : [address]"r" (addr), [val]"r" (val)
		       : );
}

char readb(iomem addr)
{
	char ret;
	__asm volatile("ldrb %[dest], [ %[address] ]"
		       : [dest]"=r" (ret)
		       : [address]"r" (addr)
		       : );
	return ret;
}

unsigned int readw(iomem addr)
{
	unsigned int ret;
	__asm volatile("ldr %[dest], [ %[address] ]"
		       : [dest]"=r" (ret)
		       : [address]"r" (addr)
		       : );
	return ret;
}
