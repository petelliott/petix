
CC=pdp11-aout-gcc
CFLAGS=-nostdlib -ffreestanding

OBJCOPY=pdp11-aout-objcopy

bootloader.bin: boot.bin pboot/pboot
	cat $^ > $@


%.bin: %.o
	$(OBJCOPY) -O binary $^ $@

boot.o: boot.s
	$(CC) $(CFLAGS) $^ -o $@


.PHONY: clean pboot/pboot

pboot/pboot:
	make -C pboot pboot

clean:
	make -C pboot clean
	rm -rf *.o *.bin
