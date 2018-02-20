.POSIX:

-include params.makefile

O ?= 0
STD ?= c89
CCC ?= gcc -ggdb3 -pedantic-errors -std=$(STD) -O$(O) -Wextra
IN_EXT ?= .c
LIBS ?= -lm
OUT_EXT ?= .out
RUN ?= main
TEST ?= test

OUTS := $(addsuffix $(OUT_EXT), $(basename $(wildcard *$(IN_EXT))))

.PHONY: all clean run

all: $(OUTS)

%$(OUT_EXT): %$(IN_EXT)
	$(CCC) -o '$@' '$<' $(LIBS)

clean:
	rm -f *'$(OUT_EXT)'

run: all
	./'$(RUN)$(OUT_EXT)'

run-%: %$(OUT_EXT)
	./'$<'

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
	    echo 'ALL ASSERTS PASSED';\
	    exit 0;\
	  fi;\
	fi;\
