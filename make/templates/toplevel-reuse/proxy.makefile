.POSIX:
.PHONY: all
RULE = $(MAKE) -C ../ $@ DIR='$(notdir $(shell pwd))/' $(MAKEFLAGS)
all: ; $(RULE)
%: ; $(RULE)
