CC=g++
CFLAGS=-Wall -O2
LIBS=-lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_contrib -lopencv_legacy -lopencv_flann -lm

IN_EXT=.cpp
IN_DIR=./
OUT_DIR=_out/
OUT_EXT=.out

INS=$(wildcard $(IN_DIR)*$(IN_EXT))
INS_NODIR=$(notdir $(INS))
OUTS_NODIR=$(patsubst %$(IN_EXT),%$(OUT_EXT),$(INS_NODIR))
OUTS=$(addprefix $(OUT_DIR),$(OUTS_NODIR))

.PHONY: all mkdir clean

run: all
	./$(OUTS)

all: mkdir $(OUTS)

mkdir:
	mkdir -p "$(OUT_DIR)"

$(OUT_DIR)%$(OUT_EXT): $(IN_DIR)%$(IN_EXT)
	$(CC) $(CFLAGS) -o "$@" "$<" $(LIBS)

clean:
	rm -rf $(OUT_DIR) $(AUX_DIR)
