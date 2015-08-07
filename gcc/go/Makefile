.POSIX:
.PHONY: clean run

main.out: main.go
	# -g is required! http://stackoverflow.com/questions/25081943/no-debug-info-in-elf-executable-errno-when-running-a-binary-built-with-gccgo
	gccgo -g -o main.out main.go
	# TODO how to do it with GCC directly? How to link?
	#gcc-4.9 -c main.go
	#

clean:
	rm -f main.out main.o

run: main.out
	./main.out
