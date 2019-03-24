AROBJS=string/memcpy.o string/strncmp.o string/memset.o
ARTARGET=libc.a

.PHONY: all

$(ROOT)/lib/libc.a: $(ARTARGET)
	cp $^ $@


include ../../obj.mk
