.PHONY: all clean test

CFLAGS = -ggdb3 -std=c99 -O0

all: main.out main_r.out

main.out: f12.o main.o
	$(CC) $(CFLAGS) -o '$@' $^

main_r.out: f12_r.o main.o
	$(CC) $(CFLAGS) -o '$@' $^

f12_r.o: f1.o f2.o
	ld -o $@ -r $^

clean:
	rm -f *.o *.out

test: all
	./main.out
	./main_r.out
