CFLAGS +=-nostdlib -ffreestanding

OBJS=main.o term.o disk.o input.o readfile.o $(BUILDROOT)/kernel/drivers/drivers.a $(BUILDROOT)/lib/libc/libc.a \
	 $(BUILDROOT)/kernel/debug.o

$(ROOT)/boot/pboot: $(OBJS)
	$(CC) -T pboot.ld $(CFLAGS) $^ -lgcc -o $@ -s

%.o: %.s
	$(CC) $(CFLAGS) -c $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

.PHONY: clean

clean:
	rm -rf *.o $(ROOT)/boot/pboot

include ../../extern.mk
