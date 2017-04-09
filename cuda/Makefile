.POSIX:

.PHONY: all

CCC ?= nvcc
IN_EXT ?= .cu
OUT_EXT ?= .out

OUTS := $(addsuffix $(OUT_EXT), $(basename $(wildcard *$(IN_EXT))))

all: $(OUTS)

%$(OUT_EXT): %$(IN_EXT)
	$(CCC) -o '$@' '$<'

clean:
	rm *'$(OUT_EXT)'
