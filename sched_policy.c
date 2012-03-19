#include "misc/addresses.h"

void _set_next_task()
{
  //Round robin.
  PCB_HEAD = PCB_HEAD->next;
}
