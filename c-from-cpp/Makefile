.POSIX:
.PHONY: run clean

main.out: main.o c.o
	g++ -o '$@' $^

c.o: c.c
	gcc -c -g -o '$@' -std=c89 -Wall -Wextra -pedantic-errors '$<'

main.o: main.cpp
	g++ -c -g -o '$@' -std=c++98 -Wall -Wextra -pedantic-errors '$<'

run: main.out
	./main.out

clean:
	rm -f *.o *.out
