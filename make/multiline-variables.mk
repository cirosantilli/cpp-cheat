.POSIX:

# This does not work: unquoted variable error.
multiline_inner := multiline_2
define multiline =
@echo multiline_1
@echo $(multiline_inner)
endef

.PHONY: all

all:
	@# [ "$(multiline_TODO)" = "$$(printf '1\n2)"' ]
