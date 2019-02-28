
OBJS=main.o mkfs.o

$(TOOLDIR)/mkfs: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.s
	$(CC) $(CFLAGS) -c $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

.PHONY: clean

clean:
	rm -rf *.o $(TOOLDIR)/mkfs
