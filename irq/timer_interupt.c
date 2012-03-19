#include "../misc/addresses.h"
#include "../scheduling/pcb.h"

void _irq_timer_handle()
{
  // Increment the tick number.
  (*TIMER_TICKS) += 1;

  // Calculate the new interupt time.
  (*TIMER_CMP_REG) = ((*TIMER_CMP_REG + 20) % 256);

  // Context switch on timers.
  SHOULD_CTX_SWITCH = 1;
}
