CFLGS := -Wall

.PHONY: all clean run

all: maina.out mainso.out mainso_fullpath.out libab.so

run: maina.out mainso.out mainso_fullpath.out
	./maina.out
	# This works only after install target and is the standard production method:
	#./mainso.out
	# This only a test method:
	env LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH ./mainso.out
	# Full path is stored in the out.
	# Since it starts with './', linker knows it is an absolute path:
	./mainso_fullpath.out

install:
	#sudo mv libabso /some/where/in/ld/path/
		#load path can be found with:
		#ldconfig -v 2>/dev/null | grep -v $'^\t'
	#sudo ldconfig

# Main to link to .so
# readout -d shows that the ouptut stores the relative path
mainso.out: main.o libab.so
	gcc $(CFLGS) -L"." main.o -o mainso.out -lab
		#will look for lib with basename *exactly* `libab.so`,
		#`libab.so.1` will not do!
	#gcc $(CFLGS) -L"." main.o -o mainso.out -l:libab.so
		#with ':' uses full basename
		#APPLICATION
		#select an specific version such as `libab.so.1`
	#env LIBRARY_PATH=$LIBRARY_PATH:. gcc $(CFLGS) main.c -o mainso.out -lab

# This is not recommended
# Better use linker path as in mainso.out
# readout -d shows that the ouptut stores the full path.
mainso_fullpath.out: main.o libab.so
	gcc $(CFLGS) main.o "$(shell realpath libab.so)" -o mainso_fullpath.out
	#gcc $(CFLGS) main.o -o mainso_fullpath.out -l"$(shell realpath libab.so)" 
		#does not work

#main with .a
maina.out: main.o ab.a
	gcc $(CFLGS) main.o ab.a -o maina.out

#make .so
libab.so: a.o b.o
	gcc $(CFLGS) -shared a.o b.o -o libab.so
	#gcc $(CFLGS) -shared -Wl,-soname,libab.so a.o b.o -o libab.so

#make .a
ab.a: a.o b.o
	ar rcs ab.a a.o b.o

#first compile the object files
#this way, if a c file does not change,
#the corresponding .o file does not get recompiled!
%.o: %.c
	gcc $(CFLGS) -fPIC -c "$<" -o "$@"

clean:
	rm -rf *.o *.a *.so *.out
