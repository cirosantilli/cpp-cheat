.POSIX:

.PHONY: all clean

all:
	swig -python -o example_wrap_py.c example.i
	python setup.py build_ext --inplace
	swig -java -o example_wrap_java.c example.i
	gcc -shared -fpic -o libexample_java.so -I"$${JAVA_HOME}/include" -I"$${JAVA_HOME}/include/linux" example.c example_wrap_java.c
	javac exampleJNI.java Main.java

clean:
	rm -rf \
		*.class \
		*.pyc \
		*.so \
		build/ \
		example.java \
		example.py \
		exampleJNI.java \
		example_wrap_*.c

test: all
	[ "$$(python main.py)" = '24' ]
	[ "$$(java -Djava.library.path=. -ea Main)" = '24' ]
