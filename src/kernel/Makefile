CFLAGS +=-nostdlib -ffreestanding

OBJS=debug.o
ARCHIVES=drivers/drivers.a fs/fs.a


.PHONY: all clean

all: dir $(ROOT)/petix

$(ROOT)/petix: $(OBJS) kernel.ld
	$(CC) $(CFLAGS) $(OBJS) $(ARCHIVES) -lgcc -T kernel.ld -o $@

DIRS=drivers fs
PATHS=$(ROOT)

clean: dirclean objclean

include ../dir.mk
include ../obj.mk
