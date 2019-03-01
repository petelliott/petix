BS_CC=pdp11-aout-gcc
OBJCOPY=pdp11-aout-objcopy

OBJS=main.o sectors.o rdfs.o
BOOTSECTORS=bootsectors/rk.inc

$(TOOLDIR)/mkboot: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

sectors.o: sectors.c $(BOOTSECTORS)
	$(CC) $(CFLAGS) -c sectors.c -o $@

bootsectors/%.inc: bootsectors/%.bin
	xxd -i < $^ > $@

bootsectors/%.bin: bootsectors/%.out
	$(OBJCOPY) -O binary $^ $@

bootsectors/%.out: bootsectors/%.s
	$(BS_CC) -nostdlib -ffreestanding $^ -o $@

.PHONY: clean

clean:
	rm -rf *.o $(TOOLDIR)/mkboot bootsectors/*.out
	rm -rf bootsectors/*.bin bootsectors/*.inc
