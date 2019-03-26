.PHONY: dir dirclean $(DIRS) $(PATHS)

dir: $(DIRS) $(PATHS)

dirclean:
	for x in $(DIRS); do make -C $$x clean; done;
	rm -rf $(PATHS)

$(PATHS):
	mkdir -p $@

$(DIRS): $(PATHS)
	make -C $@
