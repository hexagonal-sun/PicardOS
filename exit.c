void _exit()
{
	unsigned int* resetAddress = (unsigned int*)0x10000020;
	(*resetAddress) = 1;
}
