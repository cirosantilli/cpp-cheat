.PHONY: run clean

main.out: main.o f.o
	gcc -o main.out main.o f.o -l:libgfortran.so.3

run: main.out
	./main.out

main.o: main.c
	gcc -c "$<" -o "$@"

f.o: f.f
	gfortran -c "$<" -o "$@"

clean:
	rm -rf *.o *.out
