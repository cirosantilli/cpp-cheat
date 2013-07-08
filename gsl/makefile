#compiles all files in current dir into a single output file

AUX_DIR			?= _aux/
AUX_EXT			?= .o
CC						?= g++
CFLGS				?= -Wall -std=c++0x -pedantic-errors -O3
DEFINES			?= #-DPOSIX #for -DDEBUG and -DPROFILE, used dedicated DEFINES
IN_EXT				?= .c
IN_DIR				?= ./
INCLUDE_DIRS	?= #-I/usr/include/GL
LIBS					?=  -lgsl -lgslcblas -lm -lplplotd
PREDEF				?= #-DDEBUG -DPROFILE -DWINDOWS 				#preprocessor defines
RUN_ARGS			?= #0 1																	#passed as command line args to bin on run
OUT_DIR			?= _out/
OUT_NAME   	?= main
OUT_EXT			?= .elf

INS:=$(wildcard $(IN_DIR)*$(IN_EXT))
INS_NODIR:=$(notdir $(INS))
AUXS_NODIR:=$(patsubst %$(IN_EXT),%$(AUX_EXT),$(INS_NODIR))
AUXS:=$(addprefix $(AUX_DIR),$(AUXS_NODIR))
OUT_BNAME:=$(OUT_NAME)$(OUT_EXT)
OUT:=$(OUT_DIR)$(OUT_BNAME)

.PHONY: all mkdir clean assembler debug set_debug_flags profile set_profile_flags help install-deps-ubuntu

all: mkdir $(OUT)

run: all
	( cd $(OUT_DIR) && ./$(OUT_BNAME) $(RUN_ARGS) )

$(OUT): $(AUXS)
	$(CC) $(PROFILE_FLAGS) $^ -o "$@" $(LIBS)

$(AUX_DIR)%$(AUX_EXT): $(IN_DIR)%$(IN_EXT)
	$(CC) $(DEFINES) $(PREDEF) $(INCLUDE_DIRS) $(CFLAGS) -c "$<" -o "$@"

mkdir:
	mkdir -p "$(AUX_DIR)"
	mkdir -p "$(OUT_DIR)"

clean:
	rm -rf $(AUX_DIR) $(OUT_DIR)

install-deps-ubuntu:
	sudo apt-get install -y libgsl0-dev gsl-doc-info
	#if you will use plplot:
		sudo apt-get install -y libplplot-dev plplot11-driver-xwin
