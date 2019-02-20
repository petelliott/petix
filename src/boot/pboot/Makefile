CFLAGS +=-nostdlib -ffreestanding

OBJS=main.o term.o disk.o input.o

$(ROOT)/boot/pboot: $(OBJS)
	$(CC) -T pboot.ld $(CFLAGS) $^ -o $@ -s

%.o: %.s
	$(CC) $(CFLAGS) -c $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

.PHONY: clean

clean:
	rm -rf *.o $(ROOT)/boot/pboot
