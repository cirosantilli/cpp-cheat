CFLGS := -Wall

.PHONY: all clean run 

all: maina.elf mainso.elf mainso_fullpath.elf libab.so

run: maina.elf mainso.elf mainso_fullpath.elf
	./maina.elf
	#./mainso.elf
		#this works only after install target
		#and is the standard production method
	env LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH ./mainso.elf
		#this is only a test method
	./mainso_fullpath.elf
		#full path is stored in the elf
		#since it starts with './', linker knows it is an abs path

install:
	#sudo mv libabso /some/where/in/ld/path/
		#load path can be found with:
		#ldconfig -v 2>/dev/null | grep -v $'^\t'
	#sudo ldconfig

#main to link to .so
#readelf -d shows that the ouptut stores the relative path
mainso.elf: main.o libab.so
	gcc $(CFLGS) -L"." main.o -o mainso.elf -lab
		#will look for lib with basename *exactly* ``libab.so``,
		#``libab.so.1`` will not do!
	#gcc $(CFLGS) -L"." main.o -o mainso.elf -l:libab.so
		#with ':' uses full basename
		#APPLICATION
		#select an specific version such as ``libab.so.1``
	#env LIBRARY_PATH=$LIBRARY_PATH:. gcc $(CFLGS) main.c -o mainso.elf -lab

#this is not recommended
#better use linker path as in mainso.elf
#readelf -d shows that the ouptut stores the full path
mainso_fullpath.elf: main.o libab.so
	gcc $(CFLGS) main.o "$(shell realpath libab.so)" -o mainso_fullpath.elf
	#gcc $(CFLGS) main.o -o mainso_fullpath.elf -l"$(shell realpath libab.so)" 
		#does not work

#main with .a
maina.elf: main.o ab.a
	gcc $(CFLGS) main.o ab.a -o maina.elf

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
	rm -rf *.o *.a *.so *.elf
