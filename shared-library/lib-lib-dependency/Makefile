CC := gcc -pedantic-errors -std=c89 -Wall -Wextra

.PHONY: all clean run

main.out: main.o libcirosantilli_a.so
	$(CC) -L'.' main.o -o '$@' -lcirosantilli_a
	@#LD_LIBRARY_PATH=. $(CC) -L'.' main.o -o '$@' -lcirosantilli_a

run: main.out
	LD_LIBRARY_PATH=. ./main.out

libcirosantilli_a.so: a.o libcirosantilli_b.so
	@# This adds an RPATH=. field to readelf -d.
	$(CC) -L'.' -Wl,-rpath,. -shared a.o -o '$@' -lcirosantilli_b
	@#
	@# These don't add RPATH, and main.out link fails,
	@# unless you compile with LD_LIBRARY_PATH=. ? So LD_LIBRARY_PATH IS
	@# used during compile time as well, OMG.
	@# `man ld` explains rpath vs rpath-link, but it is impossible to understand.
	@#$(CC) -L'.' -shared a.o -o '$@' -lcirosantilli_b
	@#$(CC) -L'.' -Wl,-rpath-link,. -shared a.o -o '$@' -lcirosantilli_b

libcirosantilli_b.so: b.o
	$(CC) -shared '$<' -o '$@'

%.o: %.c
	$(CC) -fPIC -c '$<' -o '$@'

clean:
	rm -rf *.o *.a *.so *.out
