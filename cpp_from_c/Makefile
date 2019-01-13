.POSIX:

.PHONY: run clean

main.out: main.o notmain.o
	g++ -o '$@' $^

notmain.o: notmain.cpp
	g++ -c -g -o '$@' -pedantic-errors -std=c++98 -Wall -Wextra '$<'

main.o: main.c
	gcc -c -g -o '$@' -pedantic-errors -std=c89 -Wall -Wextra '$<'

clean:
	rm -f *.o *.out

test: main.out
	./main.out
