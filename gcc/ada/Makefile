.POSIX:
.PHONY: clean run

main: main.adb
	gcc -c main.adb
	gnatbind main
	gnatlink main
	# Same:
	#gnatmake main.adb

clean:
	rm -f main main.ali main.o

run: main
	./main
