CC := g++
LIBS := -lGL -lGLU -lglut -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_contrib -lopencv_legacy -lopencv_flann -lm
#compile command

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

run: all
	./"$(OUTS)"

all: mkdir $(OUTS)

$(OUT_DIR)%$(OUT_EXT): $(IN_DIR)%$(IN_EXT)
	$(CC) -o "$@" "$<" $(LIBS)

mkdir:
	mkdir -p "$(OUT_DIR)"

clean:
	rm -rf $(OUT_DIR) $(SAUX_DIR)

install-ubuntu:
	sudo apt-get install g++
	sudo apt-get install freeglut
	sudo apt-get install libopencv-dev
