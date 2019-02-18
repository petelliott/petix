

boot.bin: boot.o
	$(OBJCOPY) -O binary $^ $@

boot.o: boot.s
	$(CC) -c $^ -o $@

.PHONY: clean

clean:
	rm -rf boot.bin boot.o
