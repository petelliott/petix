.PHONY: objclean

$(ARTARGET): $(AROBJS)
	$(AR) cr $@ $?

%.o: %.s
	$(CC) $(CFLAGS) -c $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

objclean:
	rm -rf *.o $(AROBJS) *.a
