.POSIX:

.PHONY: all clean

all:
	swig -python example.i
	python setup.py build_ext --inplace

clean:
	rm -rf build example_wrap.c example.py *.pyc *.so

test: all
	[ "$$(python main.py)" = '24' ]
