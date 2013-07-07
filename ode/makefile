#compiles all files in current dir into a single output file

CC	:= g++
LIBS	:= -lode

IN_EXT 	:= .cpp
IN_DIR 	:= ./
AUX_DIR :=_aux/
AUX_EXT := .o
OUT_DIR := _out/
OUT_EXT :=

INS=$(wildcard $(IN_DIR)*$(IN_EXT))
INS_NODIR:=$(notdir $(INS))
AUXS_NODIR:=$(patsubst %$(IN_EXT),%$(AUX_EXT),$(INS_NODIR))
AUXS=$(addprefix $(AUX_DIR),$(AUXS_NODIR))
OUT=$(OUT_DIR)cheat$(OUT_EXT)

.PHONY: all clean install-deps-ubuntu mkdir run 

all: mkdir $(OUT)

$(OUT): $(AUXS)
	$(CC) $^ -o "$@" $(LIBS)

$(AUX_DIR)%$(AUX_EXT): $(IN_DIR)%$(IN_EXT)
	$(CC) -c "$<" -o "$@"

clean:
	rm -rf $(AUX_DIR) $(OUT_DIR)

install-deps-ubuntu:
	sudo apt-get install -y g++
	sudo apt-get install -y libode-dev

mkdir:
	mkdir -p "$(AUX_DIR)"
	mkdir -p "$(OUT_DIR)"

run: all
	$(OUT)
