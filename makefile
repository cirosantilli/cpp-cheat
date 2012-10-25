CC=gcc -Wall -Wno-unused-variable -Wno-unused-but-set-variable
#compiler

CXX=$(CC)
#cpp compiler

OUT_EXT=.out
#output extension

#N=c_cheatsheet
#$(CC) $(N).c -o $(N)$(OUT_EXT)
all:
	$(CC) c_cheat.c -o c_cheat$(OUT_EXT)
	$(CC) user_input.c -o user_input$(OUT_EXT)
	$(CC) test.c -o test$(OUT_EXT)
	$(CC) cstrings.c -o cstrings$(OUT_EXT)
	$(CC) file_io.c -o file_io$(OUT_EXT)
	$(CC) pointer_array.c -o pointer_array$(OUT_EXT)
	$(CXX) cpp_cheat.cpp -o cpp_cheat$(OUT_EXT)

#WARNING: IF OUT_EXT == "", you are going to DELETE ALL YOUR FILES!!!!!
#find . -iname "*$(OUT_EXT)" -delete 
clean:
	rm -rf *$(OUT_EXT) *.o *.s *.tmp

### sample from: http://mrbook.org/tutorials/make/ ###
# I am a comment, and I want to say that the variable CC will be
# the compiler to use.
#CC=g++
# Hey!, I am comment number 2. I want to say that CFLAGS will be the
# options I'll pass to the compiler.
#CFLAGS=-c -Wall

#all: hello

#hello: main.o factorial.o hello.o
	#$(CC) main.o factorial.o hello.o -o hello

#main.o: main.cpp
	#$(CC) $(CFLAGS) main.cpp

#factorial.o: factorial.cpp
	#$(CC) $(CFLAGS) factorial.cpp

#hello.o: hello.cpp
	#$(CC) $(CFLAGS) hello.cpp

#clean:
	#rm -rf *o hello

### sample from: http://mrbook.org/tutorials/make/ ###

#CC=g++
#CFLAGS=-c -Wall
#LDFLAGS=
#SOURCES=main.cpp hello.cpp factorial.cpp
#OBJECTS=$(SOURCES:.cpp=.o)
#EXECUTABLE=hello

#all: $(SOURCES) $(EXECUTABLE)
	
#$(EXECUTABLE): $(OBJECTS) 
	#$(CC) $(LDFLAGS) $(OBJECTS) -o $@

#.cpp.o:
	#$(CC) $(CFLAGS) $< -o $@
