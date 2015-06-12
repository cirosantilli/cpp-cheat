.POSIX:

-include params.makefile

O ?= 0
STD ?= c11
CCC ?= gcc -DIMPLEMENTATION_SIGNAL -DUNDEFINED_BEHAVIOUR -ggdb3 -pedantic-errors -std=$(STD) -O$(O) -Wextra -Wno-ignored-qualifiers -Wno-sign-compare -Wno-unused-variable -Wno-unused-label -Wno-unused-but-set-variable
IN_EXT ?= .c
LIBS ?= -lm
OUT_EXT ?= .out
RUN ?= main
TEST ?= test
TMP_EXT ?= .tmp

INS := $(wildcard *$(IN_EXT))
OUTS_NOEXT := $(basename $(INS))
OUTS := $(addsuffix $(OUT_EXT), $(OUTS_NOEXT))

.PHONY: all clean run

all: $(OUTS)

%$(OUT_EXT): %$(IN_EXT)
	$(CCC) -o '$@' '$<' $(LIBS)

clean:
	rm -f *'$(OUT_EXT)' *'$(TMP_EXT)'

run: all
	./'$(RUN)$(OUT_EXT)'

# If a `test` script exists, use it.
# Otherwise, run a default test script which checks if all programs exit 0.
test: all
	@\
	if [ -x $(TEST)  ]; then\
	  ./$(TEST) '$(OUT_EXT)';\
	else\
	  fail=false;\
	  for t in *"$(OUT_EXT)"; do\
	    if ! ./"$$t"; then\
	      fail=true;\
	      break;\
	    fi;\
	  done;\
	  if $$fail; then\
	    echo "ASSERT FAILED: $$t";\
	    exit 1;\
	  else\
	    echo 'ALL TESTS PASSED';\
	    exit 0;\
	  fi;\
	fi;\
