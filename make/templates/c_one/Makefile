.POSIX:

# Inputs.
CC = gcc
CFLAGS = -ggdb3 -pedantic-errors -std=$(STD) -O$(O) -Wall -Wextra
IN_EXT = .c
O = 0
OBJ_EXT = .o
OUT_EXT = .out
RUN = main
STD = c99

# Inputs.
INS = $(wildcard *$(IN_EXT))
OBJS = $(INS:$(IN_EXT)=$(OBJ_EXT))
RUN_BASENAME = $(RUN)$(OUT_EXT)

.PHONY: clean run

$(RUN_BASENAME): $(OBJS)
	$(CC) $(CFLAGS) -o '$@' $^

%$(OBJ_EXT): %$(IN_EXT)
	$(CC) $(CFLAGS) -c '$<' -o '$@'

clean:
	rm -f *'$(OBJ_EXT)' '$(RUN_BASENAME)'

run: $(RUN_BASENAME)
	./'$(RUN_BASENAME)'
