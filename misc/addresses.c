struct pcb;

unsigned int* const TIMER_ADDRESS = (unsigned int*)0x10000008;
unsigned int* const TIMER_CMP_REG = (unsigned int*)0x1000000C;
unsigned int* const TIMER_TICKS = (unsigned int*)0x0007FFFC;
struct pcb* PCB_HEAD = 0;
unsigned char SHOULD_CTX_SWITCH = 0;
unsigned int* PCB_BASE = (unsigned int*)0x0007FFF0;
unsigned int* NEXT_FREE_STACK = (unsigned int*)0x00027C00;
