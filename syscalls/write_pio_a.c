void _write_pio_a()
{
  int val;
  // get the value from r0.
  __asm__ volatile("mov %[value], r0" : [value] "=r" (val));
  unsigned int* pio_a_address = (unsigned int*)0x10000000;
  (*pio_a_address) = val;
}


void write_pio_a(unsigned int val)
{
  __asm__ volatile("mov r0, %[value]\n"
		   "svc 0" :: [value] "r" (val) : "cc", "lr");
}
