#ifndef __PCB_H_
#define __PCB_H_


struct pcb
{
  unsigned int regs[17];
  struct pcb* next;
};

#endif
