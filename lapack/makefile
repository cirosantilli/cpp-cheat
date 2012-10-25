CC=gcc -Wall -Wno-unused-variable -Wno-unused-but-set-variable
#compiler

CXX=$(CC)
#cpp compiler

OUT_EXT=.out
#output extension

LIBS=-lblas -llapack

SRCS = $(wildcard *.c)
PROGS = $(patsubst %.c,%,$(SRCS))
all: $(PROGS)
%: %.c
	$(CC) $(CFLAGS) -o $@$(OUT_EXT) $< $(LIBS)

clean:
	rm -rf *$(OUT_EXT) *.o *.s *.tmp
