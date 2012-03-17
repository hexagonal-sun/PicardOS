void _halt()
{
  unsigned int* resetAddress = (unsigned int*)0x10000020;
  (*resetAddress) = 1;
}


void halt()
{
  __asm__ volatile("svc 0");
}
