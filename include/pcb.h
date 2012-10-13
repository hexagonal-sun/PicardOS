#ifndef __PCB_H_
#define __PCB_H_

struct pcb
{
  unsigned int regs[17];
  struct pcb* next;
  struct pcb* prev;
};

struct pcb *PCB_HEAD;

/*
 * Whether to perform a context switch at the end of this interrupt
 * context.
 */
unsigned char SHOULD_CTX_SWITCH;

#endif
