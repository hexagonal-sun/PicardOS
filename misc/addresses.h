#include "../scheduling/pcb.h"

// Declare some usefull addresses.
unsigned int* const TIMER_ADDRESS;
unsigned int* const TIMER_CMP_REG;
unsigned int* const TIMER_TICKS;

// OS Scheduling addresses.
struct pcb* PCB_HEAD;
unsigned char SHOULD_CTX_SWITCH;
unsigned int* PCB_BASE;
unsigned int NEXT_FREE_STACK;

// IO addresses.
volatile unsigned int* PIO_A;
volatile unsigned int* PIO_B;
