IN_EXT ?= .c
OUT_EXT ?= .out
RUN ?= hello_world

INS	:= $(wildcard *$(IN_EXT))
OUTS := $(patsubst %$(IN_EXT),%$(OUT_EXT),$(INS))

.PHONY: all clean run

all: $(OUTS)

%$(OUT_EXT): %$(IN_EXT)
	gcc -pedantic-errors -std=c99 -o '$@' -Wall '$<' -lX11

clean:
	rm -f *$(OUT_EXT)

run: all
	./$(RUN)$(OUT_EXT)
