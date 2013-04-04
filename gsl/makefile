#compiles all files in current dir into a single output file

override AUX_DIR			?= _aux/
override AUX_EXT			?= .o
override CC						?= g++
override CFLGS				?= -Wall -std=c++0x -pedantic-errors -O3
override DEFINES			?= #-DPOSIX #for -DDEBUG and -DPROFILE, used dedicated DEFINES
override IN_EXT				?= .c
override IN_DIR				?= ./
override INCLUDE_DIRS	?= -I/usr/include/GL
override LIBS					?=  -lgsl -lgslcblas -lm
override PREDEF				?= #-DDEBUG -DPROFILE -DWINDOWS 				#preprocessor defines
override RUN_ARGS			?= #0 1																	#passed as command line args to bin on run
override OUT_DIR			?= _out/
override OUT_NAME   	?= main
override OUT_EXT			?= .elf

INS:=$(wildcard $(IN_DIR)*$(IN_EXT))
INS_NODIR:=$(notdir $(INS))
AUXS_NODIR:=$(patsubst %$(IN_EXT),%$(AUX_EXT),$(INS_NODIR))
AUXS:=$(addprefix $(AUX_DIR),$(AUXS_NODIR))
OUT_BNAME:=$(OUT_NAME)$(OUT_EXT)
OUT:=$(OUT_DIR)$(OUT_BNAME)

.PHONY: all mkdir clean assembler debug set_debug_flags profile set_profile_flags help install_ubuntu_deps

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

install_ubuntu_deps:
	sudo aptitude install -y libgsl0-dev gsl-doc-info
