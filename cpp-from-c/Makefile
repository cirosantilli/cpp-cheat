.POSIX:
.PHONY: run clean

main.out: main.o cpp.o
	g++ -o '$@' $^

cpp.o: cpp.cpp
	g++ -c -o '$@' -pedantic-errors -std=c++98 -Wextra '$<'

main.o: main.c
	gcc -c -o '$@' -pedantic-errors -std=c89 -Wextra '$<'

run: main.out
	./main.out

clean:
	rm -f *.o *.out
