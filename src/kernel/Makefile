


OBJS=drivers/drivers.a

.PHONY: all

all: dir $(ROOT)/petix

$(ROOT)/petix: $(OBJS) kernel.ld
	$(CC) $(CFLAGS) $(OBJS) -T kernel.ld -o $@

DIRS=drivers
PATHS=$(ROOT)

include ../dir.mk
