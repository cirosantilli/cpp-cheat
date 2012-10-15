CC=gcc #compiler
CPC=gcc #cpp compiler
OUT_EXT=.out #output extension

all:
	$(CC) c_cheatsheet.c -o c_cheatsheet$(OUT_EXT)
	$(CPC) cpp_cheatsheet.cpp -o cpp_cheatsheet$(OUT_EXT)

#build dependencies
#hello.o: hello.cpp
	#g++ -c hello.cpp 

clean:
	find . -iname "*$(OUT_EXT)" -delete 
	#rm -rf *$(OUT_EXT)

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
