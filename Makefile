CC=gcc
AS=as
CFLAGS=-static -nostdlib -O0 --std=c99 -march=armv4 -mno-thumb-interwork
LDFLAGS=-T memmap -

%.elf: %.o vectors.o exit.o svc.o syscallentry.o syscalls/write_pio_a.o
	$(CC) -T memmap -static -nostdlib vectors.o svc.o syscallentry.o syscalls/write_pio_a.o exit.o $< -o $@

%.bin: %.elf
	objcopy -O binary $< $@

%.kmd: %.bin convert.py
	python2 convert.py $< > $@


