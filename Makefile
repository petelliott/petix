

ROOT=$(shell realpath root)
TOOLDIR=$(shell realpath tools)

export

.PHONY: all clean

all:
	make -C src/

clean:
	make -C src/ clean
