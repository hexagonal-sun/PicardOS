CC=gcc
AS=as
CFLAGS=-static -nostdlib -O0 --std=c99 -march=armv4 -mno-thumb-interwork -fno-builtin -g3

objects=vectors.o exit.o syscalls/syscallentry.o syscalls/write_pio_a.o \
syscalls/get_timer_val.o syscalls/halt.o irq/irq_entry.o irq/timer_interupt.o \
setup/timer_setup.o misc/addresses.o syscalls/fork.o scheduling/task_switch.o \
scheduling/sched_policy.o

%.elf: %.o $(objects)
	$(CC) -T memmap -static -fno-builtin -nostdlib $(objects) $< -o $@

%.bin: %.elf
	objcopy -O binary $< $@

%.kmd: %.bin convert.py
	python2 convert.py $< > $@


