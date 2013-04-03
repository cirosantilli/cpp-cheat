.PHONY: run clean 

main.elf: main.o f.o
	gcc -o main.elf main.o f.o -l:libgfortran.so.3

run: main.elf
	./main.elf

main.o: main.c
	gcc -c "$<" -o "$@"

f.o: f.f
	gfortran -c "$<" -o "$@"

clean:
	rm -rf *.o *.elf
