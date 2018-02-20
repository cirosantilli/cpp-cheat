.POSIX:

O ?= 0
STD ?= c89
CCC ?= gcc -ggdb3 -pedantic-errors -std=$(STD) -O$(O) -Wextra
IN_EXT ?= .c
OUT_EXT ?= .out
RUN ?= main
TMP_EXT ?= .o

INS := $(wildcard *$(IN_EXT))
OUTS := $(INS:$(IN_EXT)=$(TMP_EXT))
RUN_BASENAME := $(RUN)$(OUT_EXT)

.PHONY: clean run

$(RUN_BASENAME): $(OUTS)
	$(CCC) -o '$@' $+

%$(TMP_EXT): %$(IN_EXT)
	$(CCC) -c '$<' -o '$@'

clean:
	rm -f *'$(TMP_EXT)' '$(RUN_BASENAME)'

run: $(RUN_BASENAME)
	./'$(RUN_BASENAME)'
