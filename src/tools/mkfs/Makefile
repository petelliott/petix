
OBJS=main.o mkfs.o

$(TOOLDIR)/mkfs: $(OBJS)
	$(TOOL_CC) $(CFLAGS) $^ -o $@

%.o: %.s
	$(TOOL_CC) $(CFLAGS) -c $^ -o $@

%.o: %.c
	$(TOOL_CC) $(CFLAGS) -c $^ -o $@

.PHONY: clean

clean:
	rm -rf *.o $(TOOLDIR)/mkfs
