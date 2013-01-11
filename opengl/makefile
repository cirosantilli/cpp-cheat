CC=gcc
LIBS=-lglut -lGLU
#compile command

INCLUDES=-I/usr/include/GL
#ubuntu path

IN_EXT=.cpp
#extension of input files

IN_DIR=./
#directory from which input files come. slash termianted.

OUT_DIR=_out/
#dir where output files such as .pdf will be put. slash terminated.

OUT_EXT=
#extension of output

INS=$(wildcard $(IN_DIR)*$(IN_EXT))
INS_NODIR=$(notdir $(INS))
OUTS_NODIR=$(patsubst %$(IN_EXT),%$(OUT_EXT),$(INS_NODIR))
OUTS=$(addprefix $(OUT_DIR),$(OUTS_NODIR))

.PHONY: all mkdir clean

all: mkdir $(OUTS)

$(OUT_DIR)%$(OUT_EXT): $(IN_DIR)%$(IN_EXT)
	$(CC) $(INCLUDES) -o "$@" "$<" $(LIBS)

mkdir:
	mkdir -p "$(OUT_DIR)"

clean:
	rm -rf $(OUT_DIR) $(AUX_DIR)
