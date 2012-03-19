#include "../misc/addresses.h"
#include "../misc/pcb.h"

void _fork()
{
  unsigned int start_address;
  unsigned int stack_size;
  // get the value from r0.
  __asm__ volatile("mov %[sa], r0\n"
		   "mov %[ss], r1"
		   : [sa] "=r" (start_address),
		     [ss] "=r" (stack_size));

  PCB_BASE -= sizeof(struct pcb);

  struct pcb* new_pcb = (struct pcb*)PCB_BASE;

  // set the PC.
  new_pcb->regs[16] = start_address;

  // set the stack.
  new_pcb->regs[13] = NEXT_FREE_STACK;
  NEXT_FREE_STACK -= stack_size;


  // set the CPSR
  new_pcb->regs[15] = 0x10;

  if(PCB_HEAD == 0)
    {
      PCB_HEAD = new_pcb;
      new_pcb->next = new_pcb;
    }
  else
    {
      new_pcb->next = PCB_HEAD->next;
      PCB_HEAD->next = new_pcb;
    }
}


void fork(unsigned int start_address,
	  unsigned int stack_size)
{
  __asm__ volatile("mov r0, %[sa]\n"
		   "mov r1, %[ss]\n"
		   "svc 3"
		   :: [sa] "r" (start_address),
		   [ss] "r" (stack_size) : "r0", "r1");
}
