.POSIX:

-include params.makefile

DIRS ?= . d e
G ?= gdb3
O ?= 0
STD ?= c11
CCC ?= gcc
CCFLAGS ?= -DIMPLEMENTATION_SIGNAL -DUNDEFINED_BEHAVIOUR -g$(G) -pedantic-errors -std=$(STD) -O$(O) -Wextra -Wno-ignored-qualifiers -Wno-sign-compare -Wno-unused-variable -Wno-unused-label -Wno-unused-but-set-variable
IN_EXT ?= .c
LIBS ?= -lm
OUT_EXT ?= .out
RUN ?= main
TEST ?= test
TMP_EXT ?= .o

INS := $(foreach DIR,$(DIRS),$(wildcard $(DIR)/*$(IN_EXT)))
OUTS_NOEXT := $(basename $(INS))
OUTS := $(addsuffix $(TMP_EXT), $(OUTS_NOEXT))
RUN_BASENAME := $(RUN)$(OUT_EXT)

.PHONY: clean run

$(RUN_BASENAME): $(OUTS)
	$(CCC) $(CCFLAGS) -o '$@' $+ $(LIBS)

%$(TMP_EXT): %$(IN_EXT)
	$(CCC) $(CCFLAGS) -c '$<' -o '$@' $(LIBS)

clean:
	for d in $(DIRS); do rm -f "$$d"/*'$(TMP_EXT)'; done
	rm -f '$(RUN_BASENAME)'

run: $(RUN_BASENAME)
	./'$(RUN_BASENAME)'
