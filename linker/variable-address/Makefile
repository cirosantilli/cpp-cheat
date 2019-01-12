.PHONY: clean test

main.out: main.c link.ld
	gcc -fno-pie -no-pie -o '$@' -std=c99 -Wall -Wextra -pedantic $^

test: main.out
	[ "$$(./'$<')" = "$$(printf 'adr 0x12345678\nval 0x9abcdef0\nval 0x0')" ]

clean:
	rm -f main.out
