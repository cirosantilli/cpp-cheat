.PHONY: all clean run 

all: maina.out mainso.out mainso_fullpath.out libab.so

#run both mains
run: maina.out mainso.out mainso_fullpath.out
	./maina.out
	#./mainso.out
		#this works only after install target
		#and is the standard production method
	env LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH ./mainso.out
		#this is only a test method
	./mainso_fullpath.out
		#full path is stored in the elf
		#since it starts with './', linker knows it is an abs path

install:
	#sudo mv libabso /some/where/in/ld/path/
		#load path can be found with:
		#ldconfig -v 2>/dev/null | grep -v $'^\t'
	#sudo ldconfig

#main to link to .so
#readelf -d shows that the ouptut stores the relative path
mainso.out: main.o libab.so c.o
	g++ -L"." main.o -o mainso.out c.o -lab
		#will look for lib with basename *exactly* ``libab.so``,
		#``libab.so.1`` will not do!
	#g++ -L"." main.o -o mainso.out -l:libab.so
		#with ':' uses full basename
		#APPLICATION
		#select an specific version such as ``libab.so.1``
	#env LIBRARY_PATH=$LIBRARY_PATH:. g++ main.cpp -o mainso.out -lab

#this is not recommended
#better use linker path as in mainso.out
#readelf -d shows that the ouptut stores the full path
mainso_fullpath.out: main.o libab.so c.o
	g++ main.o "$(shell realpath libab.so)" c.o -o mainso_fullpath.out
	#g++ main.o -o mainso_fullpath.out -l"$(shell realpath libab.so)" 
		#does not work

#main with .a
maina.out: main.o ab.a c.o
	g++ main.o ab.a c.o -o maina.out

#fortran TODO get thit to work
#maina.out: main.o ab.a c.o f.o
	#g++ main.o ab.a c.o f.o -o maina.out

#make .so
libab.so: a.o b.o
	g++ -shared a.o b.o -o libab.so
	#g++ -shared -Wl,-soname,libab.so a.o b.o -o libab.so

#make .a
ab.a: a.o b.o
	ar rcs ab.a a.o b.o

#first compile the object files
#this way, if a cpp file does not change,
#the corresponding .o file does not get recompiled!
%.o: %.cpp
	g++ -fPIC -c "$<" -o "$@"

c.o: c.c
	g++ -c "$<" -o "$@"
	#gcc -c "$<" -o "$@"
		#fails
		#why?

f.o: f.f
	gfortran -c "$<" -o "$@"

clean:
	rm -rf *.o *.a *.so *.out
