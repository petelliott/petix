
CC=pdp11-aout-gcc
AR=pdp11-aout-ar

BUILDROOT=$(shell pwd)
#CFLAGS= -O2 -Wall -I$(BUILDROOT)/include/include -nostdlib
CFLAGS =-Wall -g -I$(BUILDROOT)/include/include -nostdlib
export

DIRS=boot include tools kernel lib
PATHS=$(ROOT)

include dir.mk

.PHONY: clean
clean: dirclean

