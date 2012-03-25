#include "../misc/addresses.h"
#include "../scheduling/pcb.h"
#include "../scheduling/util.h"

void exit();

void _fork(unsigned int start_address,
           unsigned int stack_size)
{
  PCB_BASE -= sizeof(struct pcb);

  struct pcb* new_pcb = (struct pcb*)PCB_BASE;

  // set the PC.
  new_pcb->regs[16] = start_address;

  // set the CPSR
  new_pcb->regs[15] = 0x10;

  // Set the LR to the exit function.
  new_pcb->regs[14] = (unsigned int)&exit;

  // set the stack.
  new_pcb->regs[13] = NEXT_FREE_STACK;
  NEXT_FREE_STACK -= stack_size;

  // Add the new task to the run-queue.
  add_to_queue(new_pcb, &PCB_HEAD);
}


void fork(unsigned int start_address,
          unsigned int stack_size)
{
	__asm__ volatile("svc 3");
}
