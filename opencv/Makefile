# TODO how to factor out the makefile for this case and symlink to the general Makefile?
# The problem is that the compiled output needs input files (sky.jpg) to work with
# and those files must be put on the same output directory as the executable (_out)
# This would need a post build hook.

CC		:= g++
CFLAGS 	:= -Wall -O2
LIBS 	:= -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_contrib -lopencv_legacy -lopencv_flann -lm

IN_EXT	:= .cpp
IN_DIR	:= ./
OUT_DIR	:= _out/
OUT_EXT	:=

INS			:= $(wildcard $(IN_DIR)*$(IN_EXT))
INS_NODIR	:= $(notdir $(INS))
OUTS_NODIR	:= $(patsubst %$(IN_EXT),%$(OUT_EXT),$(INS_NODIR))
OUTS 		:= $(addprefix $(OUT_DIR),$(OUTS_NODIR))

RUN := main

.PHONY: all mkdir clean

all: mkdir $(OUTS)

run: all
	./$(OUT_DIR)$(RUN)$(OUT_EXT)

mkdir:
	mkdir -p "$(OUT_DIR)"

$(OUT_DIR)%$(OUT_EXT): $(IN_DIR)%$(IN_EXT)
	$(CC) $(CFLAGS) -o "$@" "$<" $(LIBS)

clean:
	rm -rf $(OUT_DIR) $(AUX_DIR)

deps:
	sudo apt-get install -y libopencv-dev opencv-doc
