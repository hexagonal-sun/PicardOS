#include "../misc/addresses.h"

void _timer_setup()
{
  // get the current timer val.
  unsigned char current_timer_val = (*TIMER_ADDRESS);

  // The timer runs at 1kHz, we want to interupt every 50Hz.
  (*TIMER_CMP_REG) = ((*TIMER_CMP_REG + 20) % 256);
}
