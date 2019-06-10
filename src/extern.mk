

.PHONY: $(EXTERNOBJS)
$(EXTERNOBJS):
	make -C $(shell dirname $@) $(shell basename $@)
