.POSIX:

STD = c99

.PHONY: all clean run

all: main.out

main.out: main.o optimize.o
	gcc -o $@ $^

main.o: main.c
	gcc -ggdb3 -O0 -c -std=$(STD) $<

optimize.o: optimize.c
	gcc -ggdb3 -O3 -c -std=$(STD) $<

run: all
	ulimit -Sv 500000 && ./main.out $(ARGS)

clean:
	rm -f *.o *.out
