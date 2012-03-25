CC=arm-elf-gcc
AS=arm-elf-as
CFLAGS=-static -nostdlib -Ofast --std=c99 -march=armv4 -mno-thumb-interwork -fno-builtin -g3 -mhard-float

all:test.elf

objects=vectors.o syscalls/syscallentry.o syscalls/write_pio_a.o \
syscalls/get_timer_val.o syscalls/halt.o irq/irq_entry.o irq/timer_interupt.o \
setup/timer_setup.o misc/addresses.o syscalls/fork.o scheduling/task_switch.o \
scheduling/sched_policy.o syscalls/exit.o scheduling/util.o syscalls/lcd_ctl.o \
syscalls/print_string.o lcd/lcd_busy.o lcd/print_char.o

%.elf: %.o $(objects)
	$(CC) -T memmap -static -fno-builtin -nostdlib $(objects) $< -o $@

%.bin: %.elf
	objcopy -O binary $< $@

%.kmd: %.bin convert.py
	python2 convert.py $< > $@

clean:
	rm -rf test.elf

.PHONY: all clean
