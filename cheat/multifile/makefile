.PHONY: all clean run 

all: maina mainso libab.so

#run: maina mainso install
	#if we had

#run both mains
run: maina mainso
	./maina.out
	env LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH ./mainso.out
		#this is only a test method
	#./mainso.out
		#this works only after install target
		#and is the standard production method

install:
	#sudo mv libabso /some/where/in/ld/path/
		#load path can be found with:
		#ldconfig -v 2>/dev/null | grep -v $'^\t'
	#sudo ldconfig

#main to link to .so
mainso: main.cpp libab.so
	g++ -L"." main.cpp -o mainso.out -lab
	#env LIBRARY_PATH=$LIBRARY_PATH:. g++ -L"." main.cpp -o mainso.out -lab
		#SAME

#main with .a
maina: main.cpp ab.a
	g++ main.cpp ab.a -o maina.out

#make .so
libab.so: a.o b.o
	g++ -shared a.o b.o -o libab.so
	#g++ -shared -Wl,-soname,libab.so a.o b.o -o libab.so

#make .a
ab.a: a.o b.o
	ar rcs ab.a a.o b.o

%.o: %.cpp
	g++ -fPIC -c "$<" -o "$@"

clean:
	rm -rf maina mainso *.o *.a *.so *.out
