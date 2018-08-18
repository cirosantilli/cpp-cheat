.POSIX:
.PHONY: run clean

main.out: main.o cpp.o
	g++ -o '$@' $^

cpp.o: cpp.cpp
	g++ -c -g -o '$@' -pedantic-errors -std=c++98 -Wall -Wextra '$<'

main.o: main.c
	gcc -c -g -o '$@' -pedantic-errors -std=c89 -Wall -Wextra '$<'

run: main.out
	./main.out

clean:
	rm -f *.o *.out
