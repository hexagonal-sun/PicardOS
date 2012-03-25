unsigned int _get_timer_val()
{
  unsigned int val;
  unsigned int* timer_address = (unsigned int*)0x10000008;
  val = (*timer_address);
  return val;
}


unsigned int get_timer_val()
{
  int val;
  __asm__ volatile("svc 1\n"
                   "mov %[value], r0" : [value] "=r" (val));
  return val;
}
