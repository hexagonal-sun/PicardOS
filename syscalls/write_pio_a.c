void _write_pio_a(unsigned int val)
{
	unsigned int* pio_a_address = (unsigned int*)0x10000000;
	(*pio_a_address) = val;
}
