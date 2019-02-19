
CC=pdp11-aout-gcc
CFLAGS=-I../kernel/include/ -nostdlib -ffreestanding

OBJCOPY=pdp11-aout-objcopy

bootloader.bin: boot.bin stage2
	cat $^ > $@

stage2: stage2.o stage2.ld
	$(CC) -T stage2.ld $(CFLAGS) stage2.o -o $@ -s


%.bin: %.o
	$(OBJCOPY) -O binary $^ $@

%.o: %.s
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

.PHONY: clean

clean:
	rm -rf *.o *.bin stage2
