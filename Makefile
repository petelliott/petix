
CC=pdp11-aout-gcc
OBJCOPY=pdp11-aout-objcopy
export

image.dsk: bootloader
	cp bootloader/boot.bin image.dsk

.PHONY: bootloader clean

clean:
	make -C bootloader clean
	rm -rf image.dsk


bootloader:
	make -C bootloader
