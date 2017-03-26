CC := gcc -pedantic-errors -std=c89 -Wall -Wextra

.PHONY: all clean run

all: main.out main1.out main2.out

run: all
	LD_LIBRARY_PATH=. ./main.out
	LD_LIBRARY_PATH=. ./main1.out
	LD_LIBRARY_PATH=. ./main2.out

main.out: main.c libcirosantilli_a.so
	$(CC) -L'.' main.c -o '$@' -lcirosantilli_a

main1.out: main.c libcirosantilli_a.so
	$(CC) -DV1 -L'.' main.c -o '$@' -lcirosantilli_a

main2.out: main.c libcirosantilli_a.so
	$(CC) -DV2 -L'.' main.c -o '$@' -lcirosantilli_a

libcirosantilli_a.so: a.o
	$(CC) -Wl,--version-script,a.map -L'.' -shared a.o -o '$@'

libcirosantilli_a.o: a.c
	$(CC) -fPIC -c '$<' -o '$@'

clean:
	rm -rf *.o *.a *.so *.out
