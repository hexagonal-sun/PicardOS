TOOLCHAIN=arm-linux-gnueabihf
CC=$(TOOLCHAIN)-gcc
AS=$(TOOLCHAIN)-as
CFLAGS=-static -nostdlib -Ofast --std=c99 -march=armv4 -mno-thumb-interwork -fno-builtin -g3 -mhard-float -marm

all: kernel.elf

objects=setup/init.o syscalls/syscallentry.o syscalls/write_pio_a.o \
syscalls/get_timer_val.o syscalls/halt.o irq/irq_entry.o irq/timer_interupt.o \
setup/timer_setup.o misc/addresses.o syscalls/fork.o scheduling/task_switch.o \
scheduling/sched_policy.o syscalls/exit.o scheduling/util.o \
syscalls/print_string.o lcd/lcd_busy.o lcd/print_char.o lcd/send_command.o \
syscalls/lcd_send_command.o test.o

%.o: %.s
	@echo "  AS	$@"
	@$(CC) $(CFLAGS) -c -o $@ $<


%.o: %.c
	@echo "  CC	$@"
	@$(CC) $(CFLAGS) -c -o $@ $<


kernel.elf: $(objects)
	@echo "  LINK	$@"
	@$(CC) -T memmap -static -fno-builtin -nostdlib $^ -o $@


clean:
	rm -rf kernel.elf $(objects)

.PHONY: all clean
