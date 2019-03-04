
%.a: $(AROBJS)
	$(AR) cr $@ $?

%.o: %.s
	$(CC) $(CFLAGS) -c $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -rf *.o $(AROBJS) *.a
