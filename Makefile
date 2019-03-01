

ROOT=$(shell realpath root)
TOOLDIR=$(shell realpath tools)

export

.PHONY: all src clean

all: src disk.img

src:
	make -C src/


clean:
	make -C src/ clean

disk.img: root/ tools/
	tools/mkfs root/ disk.img 256 128
	tools/mkboot rk0 disk.img /boot/pboot
