CC=gcc
AS=as
CFLAGS=-static -nostdlib -O0 --std=c99 -march=armv4 -mno-thumb-interwork
LDFLAGS=-T memmap -

objects=vectors.o exit.o syscalls/syscallentry.o syscalls/write_pio_a.o \
syscalls/get_timer_val.o syscalls/halt.o irq/irq_entry.o irq/timer_interupt.o \
setup/timer_setup.o misc/addresses.o

%.elf: %.o $(objects)
	$(CC) -T memmap -static -nostdlib $(objects) $< -o $@

%.bin: %.elf
	objcopy -O binary $< $@

%.kmd: %.bin convert.py
	python2 convert.py $< > $@


