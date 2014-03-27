.PHONY: run clean 

main.elf: main.o c.o
	g++ -o main.elf main.o c.o

run: main.elf
	./main.elf

main.o: main.cpp
	g++ -c "$<" -o "$@"

c.o: c.c
	g++ -c "$<" -o "$@"
	#the following does not work:!!!
		#gcc -c "$<" -o "$@"
	#because gcc gives plain names to function in the object file
	#whilt g++ uses the more complex cpp naming conventions.

clean:
	rm -rf *.o *.elf
