
CC=pdp11-aout-gcc
CFLAGS=-I../kernel/include/
OBJCOPY=pdp11-aout-objcopy

boot.bin: boot.o
	$(OBJCOPY) -O binary $^ $@

boot.o: boot.s
	$(CC) $(CFLAGS) -c $^ -o $@

.PHONY: clean

clean:
	rm -rf boot.bin boot.o
