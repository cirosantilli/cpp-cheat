.POSIX:

G ?= gdb3
IN_EXT ?= .c
IN_EXT_CPP ?= .cpp
O ?= 0
OUT_EXT ?= .out
RUN ?= count_infinite

INS := $(wildcard *$(IN_EXT))
OUTS := $(addsuffix $(OUT_EXT), $(basename $(INS)))

INS_CPP := $(wildcard *$(IN_EXT_CPP))
OUTS_CPP := $(addsuffix $(OUT_EXT), $(basename $(INS_CPP)))

.PHONY: all clean run

all: $(OUTS) $(OUTS_CPP)

%$(OUT_EXT): %$(IN_EXT)
	gcc -O'$O' -g'$(G)' -o '$@' -pedantic-errors -std=c89 -Wextra '$<'

%$(OUT_EXT): %$(IN_EXT_CPP)
	g++ -O'$O' -g'$(G)' -o '$@' -pedantic-errors -std=c++11 -Wextra '$<'

clean:
	rm -f *$(OUT_EXT)

run: all
	./'$(RUN)$(OUT_EXT)'
