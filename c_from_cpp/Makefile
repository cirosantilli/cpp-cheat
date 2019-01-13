.POSIX:

.PHONY: clean run test

main.out: main.o notmain.o
	g++ -o '$@' $^

main.o: main.cpp
	g++ -c -g -o '$@' -std=c++98 -Wall -Wextra -pedantic-errors '$<'

notmain.o: notmain.c
	gcc -c -g -o '$@' -std=c89 -Wall -Wextra -pedantic-errors '$<'

clean:
	rm -f *.o *.out

test: main.out
	./main.out
