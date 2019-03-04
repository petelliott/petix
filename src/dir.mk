.PHONY: dir clean $(DIRS) $(PATHS)

dir: $(DIRS) $(PATHS)
	echo $(DIRS) $(PATHS)

clean:
	for x in $(DIRS); do make -C $$x clean; done;
	rm -rf $(PATHS)

$(PATHS):
	mkdir -p $@

$(DIRS): $(PATHS)
	make -C $@
