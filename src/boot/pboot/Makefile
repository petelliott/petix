CFLAGS +=-nostdlib -ffreestanding

EXTERNOBJS=$(BUILDROOT)/kernel/debug.o $(BUILDROOT)/kernel/drivers/drivers.a $(BUILDROOT)/lib/libc/libc.a
OBJS=main.o term.o boot.o input.o readfile.o

$(ROOT)/boot/pboot: $(OBJS) $(EXTERNOBJS)
	$(CC) -T pboot.ld $(CFLAGS) $^ -lgcc -o $@ -s

%.o: %.s
	$(CC) $(CFLAGS) -c $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

.PHONY: clean

clean:
	rm -rf *.o $(ROOT)/boot/pboot

include ../../extern.mk
