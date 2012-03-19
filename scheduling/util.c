#include "pcb.h"

void add_to_queue(struct pcb* element, struct pcb** head)
{
  if(*head == 0)
    {
      *head = element;
      element->next = element;
      element->prev = element;
    }
  else
    {
      element->next = (*head)->next;
      element->prev = *head;
      (*head)->next->prev = element;
      (*head)->next = element;
    }
}

void remove_from_queue(struct pcb* element)
{
  if(element->next == element)
    {
      element->next = 0;
    }
  else
    {
      element->prev->next = element->next;
      element->next->prev = element->prev;
    }
}
