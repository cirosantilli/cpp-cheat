# make all files with one of the given extensions by IN_EXTS
# separatelly, possibly using a different rule per extension

IN_DIR 		?= ./
IN_EXTS 	?= .c
OUT_EXT 	?= .out
TMP_EXT 	?= .tmp
RUN			?= main

INS			:= $(foreach IN_EXT, $(IN_EXTS), $(wildcard $(IN_DIR)*$(IN_EXT)) )
INS_NODIR 	:= $(notdir $(INS))
OUTS_NODIR	:= $(basename $(INS_NODIR))
OUTS		:= $(addsuffix $(OUT_EXT), $(OUTS_NODIR))

.PHONY: all clean run

all: $(OUTS)

%$(OUT_EXT): %$(IN_EXTS)
	gcc -Wall -std=c99 -pedantic-errors -o '$@' '$<'

clean:
	rm -f *$(OUT_EXT) *$(TMP_EXT)

run: all
	./server$(OUT_EXT) &
	./client$(OUT_EXT) &
	./client$(OUT_EXT) &
	./client$(OUT_EXT) &
