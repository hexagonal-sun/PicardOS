/*
  *These I/O operations should be used when accessing memory-mapped
  *I/O.
 */

#ifndef __IO_H_
#define __IO_H_
#define iomem volatile void*
#define ioreg volatile unsigned int

#define __io_address(x) ((iomem)(x))

void writeb(char val, iomem addr);
void writew(unsigned int val, iomem addr);
volatile char readb(iomem addr);
volatile unsigned int readw(iomem addr);

#endif
