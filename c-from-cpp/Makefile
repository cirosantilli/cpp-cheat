.POSIX:
.PHONY: run clean

main.out: main.o c.o
	g++ -o '$@' $^

c.o: c.c
	gcc -c -o '$@' -std=c89 -Wextra -pedantic-errors '$<'

main.o: main.cpp
	g++ -c -o '$@' -std=c++98 -Wextra -pedantic-errors '$<'

run: main.out
	./main.out

clean:
	rm -f *.o *.out
