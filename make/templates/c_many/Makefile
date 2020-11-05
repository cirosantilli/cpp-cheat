.POSIX:

# Input parameters
CC = gcc
CFLGS = -ggdb3 -O0 -pedantic-errors -std=c99 -Wall -Wextra
IN_EXT = .c
OUT_DIR = .
OUT_EXT = .out

OUTS = $(addprefix $(OUT_DIR)/, $(addsuffix $(OUT_EXT), $(basename $(wildcard *$(IN_EXT)))))

.PHONY: all clean mkdir test

all: mkdir $(OUTS)

$(OUT_DIR)/%$(OUT_EXT): %$(IN_EXT)
	$(CC) $(CFLGS) -o '$@' '$<'

clean:
	if [ '$(OUT_DIR)' = '.' ]; then \
	  rm -f *'$(OUT_EXT)'; \
	else \
	  rm -rf '$(OUT_DIR)'; \
	fi

mkdir:
	mkdir -p '$(OUT_DIR)'

test: all
	@\
	for t in *"$(OUT_EXT)"; do\
	  if ! ./"$$t"; then\
		echo "ASSERT FAILED: $$t";\
		exit 1;\
	  fi;\
	done;\
