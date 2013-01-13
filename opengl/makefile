CC=gcc
LIBS=-lglut -lGLU
INCLUDES=-I/usr/include/GL

IN_EXT=.cpp
IN_DIR=./
OUT_DIR=_out/
OUT_EXT=

INS=$(wildcard $(IN_DIR)*$(IN_EXT))
OUT=$(OUT_DIR)cheat$(OUT_EXT)

.PHONY: all mkdir clean

all: mkdir $(OUT)

run: all
	$(OUT_DIR)cheat$(OUT_EXT)

$(OUT): $(INS)
	echo $(OUT)
	$(CC) $(INCLUDES) -o "$@" $^ $(LIBS)

mkdir:
	mkdir -p "$(OUT_DIR)"

clean:
	rm -rf $(OUT_DIR) $(AUX_DIR)
