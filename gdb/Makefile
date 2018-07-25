.POSIX:

COMMON_FLAGS = -O'$O' -g'$(G)' -pthread -Wextra
CFLAGS = $(COMMON_FLAGS) -std=c99
CXXFLAGS = $(COMMON_FLAGS) -std=c++11
G = gdb3
IN_EXT = .c
IN_EXT_CPP = .cpp
O = 0
OUT_EXT = .out
RUN = count_infinite

INS = $(wildcard *$(IN_EXT))
OUTS = $(addsuffix $(OUT_EXT), $(basename $(INS)))

INS_CPP = $(wildcard *$(IN_EXT_CPP))
OUTS_CPP = $(addsuffix $(OUT_EXT), $(basename $(INS_CPP)))

.PHONY: all clean run

all: $(OUTS) $(OUTS_CPP)

%$(OUT_EXT): %$(IN_EXT)
	gcc $(CFLAGS) -o '$@' -pedantic-errors '$<'

%$(OUT_EXT): %$(IN_EXT_CPP)
	g++ $(CXXFLAGS) -o '$@' -pedantic-errors '$<'

clean:
	rm -f *$(OUT_EXT)

run: all
	./'$(RUN)$(OUT_EXT)'
