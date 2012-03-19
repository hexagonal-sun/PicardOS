#ifndef __SCHED_UTIL_H_
#define __SCHED_UTIL_H_

void add_to_queue(struct pcb* element, struct pcb** head);
void remove_from_queue(struct pcb* element);

#endif
