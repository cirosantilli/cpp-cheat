CC := gcc -pedantic-errors -std=c89 -Wall -Wextra

.PHONY: all clean run

main.out: main.o libcirosantilli_a.so
	$(CC) -L'.' main.o -o '$@' -lcirosantilli_a

run: main.out
	LD_LIBRARY_PATH=. ./main.out

libcirosantilli_a.so: a.o
	$(CC) -Wl,--version-script,a.map -L'.' -shared a.o -o '$@'

%.o: %.c
	$(CC) -fPIC -c '$<' -o '$@'

clean:
	rm -rf *.o *.a *.so *.out
