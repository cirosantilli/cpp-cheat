#this is mostly for test purposes. see: ``makefile.individual_out_bins`` for a more complete makefile

#c/cpp
CC				?= gcc
CFLAGS		?= -Wall -std=c99 -pedantic-errors
CXX			?= g++
CXXFLAGS	?= -Wall -std=c++0x -pedantic-errors
LIBS			?= -lplplotd
DEFINES 	?=

#paths
IN_DIR 	?= ./
OUT_DIR 	?= _out/
OUT_EXT 	?=

#run
RUN ?= cheat
	#basename without extension of file to run

RUN_BNAME := $(RUN)$(OUT_EXT)

EXT:=.c
INS:=$(wildcard $(IN_DIR)*$(EXT))
INS_NODIR:=$(notdir $(INS))
OUTS_NODIR:=$(patsubst %$(EXT),%$(OUT_EXT),$(INS_NODIR))
C_OUTS:=$(addprefix $(OUT_DIR),$(OUTS_NODIR))

EXT:=.cpp
INS:=$(wildcard $(IN_DIR)*$(EXT))
INS_NODIR:=$(notdir $(INS))
OUTS_NODIR:=$(patsubst %$(EXT),%$(OUT_EXT),$(INS_NODIR))
CPP_OUTS:=$(addprefix $(OUT_DIR),$(OUTS_NODIR))

.PHONY: all mkdir clean install-deps-ubuntu

all: mkdir $(C_OUTS) $(CPP_OUTS)

install-deps-ubuntu:
	sudo apt-get install libplplot-dev plplot11-driver-xwin

mkdir:
	mkdir -p "$(OUT_DIR)"

$(OUT_DIR)%$(OUT_EXT): $(IN_DIR)%.c
	$(CC) $(CFLAGS) -o "$@" "$<" $(LIBS)

$(OUT_DIR)%$(OUT_EXT): $(IN_DIR)%.cpp
	$(CXX) $(CXXFLAGS) -o "$@" "$<" $(LIBS)

run: all
	( cd $(OUT_DIR) && ./$(RUN_BNAME) ) #run from out dir

clean:
	rm -rf "$(OUT_DIR)"
