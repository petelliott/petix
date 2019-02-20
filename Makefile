
CC=pdp11-aout-gcc
TOOL_CC=gcc

ROOT=$(shell realpath root)
TOOLDIR=$(shell realpath tools)

export

.PHONY: all clean

all:
	make -C src/

clean:
	make -C src/ clean
