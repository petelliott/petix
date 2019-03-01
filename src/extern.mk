

$(BUILDROOT)/%:
	make -C $(shell dirname $@) $(shell basename $@)
