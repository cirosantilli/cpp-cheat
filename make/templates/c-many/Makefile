.POSIX:

CC = gcc
CFLGS = -ggdb3 -O0 -pedantic-errors -std=c99 -Wall -Wextra
IN_EXT = .c
OUT_EXT = .out

OUTS = $(addsuffix $(OUT_EXT), $(basename $(wildcard *$(IN_EXT))))

.PHONY: all clean test

all: $(OUTS)

%$(OUT_EXT): %$(IN_EXT)
	$(CC) $(CFLGS) -o '$@' '$<'

clean:
	rm -f *'$(OUT_EXT)'

test: all
	@\
	for t in *"$(OUT_EXT)"; do\
	  if ! ./"$$t"; then\
		echo "ASSERT FAILED: $$t";\
		exit 1;\
	  fi;\
	done;\
