

ROOT=$(shell realpath root)
TOOLDIR=$(shell realpath tools)

export

.PHONY: all src clean

all: src disk.img

src:
	make -C src/


clean:
	make -C src/ clean

disk.img: $(wildcard src/**/*)
	tools/mkfs root/ disk.img 2048 256
	tools/mkboot rk0 disk.img /boot/pboot
