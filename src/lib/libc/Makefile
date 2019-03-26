AROBJS=string/memcpy.o string/strncmp.o string/memset.o
ARTARGET=libc.a

.PHONY: all clean

$(ROOT)/lib/libc.a: $(ARTARGET)
	cp $^ $@


clean: objclean

include ../../obj.mk
