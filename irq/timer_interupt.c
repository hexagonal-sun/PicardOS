#include <pcb.h>
#include <init.h>

unsigned int  *TIMER_ADDRESS = (unsigned int*)0x10000008;
unsigned int  *TIMER_CMP_REG = (unsigned int*)0x1000000C;
unsigned int  *TIMER_TICKS = (unsigned int*)0x0007FFFC;

void _irq_timer_handle()
{
  // Increment the tick number.
  (*TIMER_TICKS) += 1;

  // Calculate the new interupt time.
  (*TIMER_CMP_REG) = ((*TIMER_CMP_REG + 20) % 256);

  // Context switch on timers.
  SHOULD_CTX_SWITCH = 1;
}

void _timer_setup()
{
  // get the current timer val.
  unsigned char current_timer_val = (*TIMER_ADDRESS);

  // The timer runs at 1kHz, we want to interupt every 50Hz.
  (*TIMER_CMP_REG) = ((*TIMER_CMP_REG + 20) % 256);
}
init_call(_timer_setup);
