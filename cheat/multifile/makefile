.PHONY: all clean run 

all: maina mainso libab.so

#run both mains
run: maina mainso
	./maina
	./mainso

#main to link to .so
mainso: main.cpp libab.so
	g++ main.cpp -o mainso -L. -lab

#main with .a
maina: main.cpp ab.a
	g++ main.cpp ab.a -o maina

#make .so
libab.so: a.o b.o
	g++ -shared a.o b.o -o libab.so

#make .a
ab.a: a.o b.o
	ar rcs ab.a a.o b.o

%.o: %.cpp
	g++ -fPIC -c "$<" -o "$@"

clean:
	rm -rf maina mainso *.o *.a *.so
