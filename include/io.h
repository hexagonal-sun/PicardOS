/*
  *These I/O operations should be used when accessing memory-mapped
  *I/O.
 */

#ifndef __IO_H_
#define __IO_H_
#define iomem volatile void*
#define ioreg volatile unsigned int

#define __io_address(x) ((iomem)(x))


inline void writeb(unsigned int val, iomem addr)
{
	__asm("strb r0, [r1]" ::: "memory");
}

inline void writew(unsigned int val, iomem addr)
{
	__asm("str r0, [r1]" ::: "memory");
}

inline volatile unsigned int readb(iomem addr)
{
	__asm("ldrb r0, [r0]" ::: "r0");
}

inline volatile unsigned int readw(iomem addr)
{
	__asm("ldr r0, [r0]" ::: "r0");
}

#endif
