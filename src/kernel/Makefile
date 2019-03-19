
OBJS=drivers/drivers.a fs/fs.a

.PHONY: all

all: dir $(ROOT)/petix

$(ROOT)/petix: $(OBJS) kernel.ld
	$(CC) $(CFLAGS) $(OBJS) -T kernel.ld -o $@

DIRS=drivers fs
PATHS=$(ROOT)

include ../dir.mk
