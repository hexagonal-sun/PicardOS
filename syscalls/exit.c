#include <pcb.h>
#include "../scheduling/util.h"

void _exit()
{
  // Remove this process from the queue.
  remove_from_queue(PCB_HEAD);

  // Set the next task to be scheduled.
  PCB_HEAD = PCB_HEAD->next;
}


void exit()
{
  __asm__ volatile("svc 4");
}
