CC=pdp11-aout-gcc
CFLAGS=-I../../kernel/include/ -nostdlib -ffreestanding

OBJS=main.o term.o disk.o input.o

pboot: $(OBJS)
	$(CC) -T pboot.ld $(CFLAGS) $^ -o $@ -s

%.o: %.s
	$(CC) $(CFLAGS) -c $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

.PHONY: clean

clean:
	rm -rf *.o pboot
