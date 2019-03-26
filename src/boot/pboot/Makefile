CFLAGS +=-nostdlib -ffreestanding

OBJS=main.o term.o boot.o input.o readfile.o $(BUILDROOT)/kernel/debug.o \
	 $(BUILDROOT)/kernel/drivers/drivers.a $(BUILDROOT)/lib/libc/libc.a

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
