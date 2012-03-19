#include "../misc/addresses.h"

void _exit()
{
  // Remove this process from the queue.

  // If there are no more tasks left to schedule,
  // just set the null task.
  if(PCB_HEAD->next == PCB_HEAD)
    {
      PCB_HEAD = 0;
    }

  // We need to find the element that points to PCB_HEAD.
  struct pcb* before;
  before = PCB_HEAD;
  while(before->next != PCB_HEAD)
    {
      before = before->next;
    }

  // we should now have the task the points to PCB_HEAD.
  before->next = PCB_HEAD->next;

  // Set the next task to be scheduled.
  PCB_HEAD = PCB_HEAD->next;
}


void exit()
{
  __asm__ volatile("svc 4");
}
