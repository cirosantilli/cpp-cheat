.PHONY: run clean

main.out: main.o c.o
	g++ -o main.out main.o c.o

run: main.out
	./main.out

main.o: main.cpp
	g++ -c "$<" -o "$@"

c.o: c.c
	g++ -c "$<" -o "$@"
	# The following does not work:!!!
		#gcc -c "$<" -o "$@"
	# Because gcc gives plain names to function in the object file
	# While g++ uses the more complex cpp naming conventions.

clean:
	rm -f *.o *.out
