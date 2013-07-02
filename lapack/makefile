#compiles c files with gcc and c++ files with g++, one by one separatelly

#this is mostly for test purposes. see: ``makefile.individual_out_bins`` for a more complete makefile

#c/cpp
CC				?= gcc
CFLAGS		?= -Wall -std=c99 -pedantic-errors
CXX			?= g++
CXXFLAGS	?= -Wall -std=c++0x -pedantic-errors
LIBS			?= -lm -lblas -llapacke #-l:liblapack.so.3
DEFINES 	?= -DPOSIX

#fortran
FF ?= gfortran
FFLIBS ?= -l:libblas/libblas.so -l:lapack/liblapack.so
FFLAGS ?= -Wall -march=native -std=f95 -pedantic-errors  

#paths
IN_DIR 	?= ./
OUT_DIR 	?= _out/
OUT_EXT 	?= .out

#run
RUN ?= c			#basename without extension of file to run

ASSEMBLER_BASENAME ?= c.c
ASSEMBLE_EXT 			?= .c
DEBUG_DEFINE 			?=
DEBUG_FLAGS  			?=
PROFILE_DEFINE 		?= #-DDEBUG
PROFILE_FLAGS  		?= #
OPTIMIZE_FLAGS			?= #-O3

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

EXT:=.f
INS:=$(wildcard $(IN_DIR)*$(EXT))
INS_NODIR:=$(notdir $(INS))
OUTS_NODIR:=$(patsubst %$(EXT),%$(OUT_EXT),$(INS_NODIR))
F_OUTS:=$(addprefix $(OUT_DIR),$(OUTS_NODIR))

.PHONY: all mkdir clean install ubuntu_install_deps

all: mkdir $(C_OUTS) $(CPP_OUTS) $(F_OUTS)

ubuntu_install_deps:
	#blas c/fotran and lapack fortran:
		sudo aptitude install -y liblapack-dev
	#lapack c via lapacke:
		sudo aptitude install -y liblapacke-dev

mkdir:
	mkdir -p "$(OUT_DIR)"

$(OUT_DIR)%$(OUT_EXT): $(IN_DIR)%.c
	$(CC) $(CFLAGS) -o "$@" "$<" $(LIBS)

$(OUT_DIR)%$(OUT_EXT): $(IN_DIR)%.cpp
	$(CXX) $(CXXFLAGS) -o "$@" "$<" $(LIBS)

$(OUT_DIR)%$(OUT_EXT): $(IN_DIR)%.f
	$(FF) $(OPTIMIZE_FLAGS) $(FFLAGS) -o "$@" "$<" $(FFLIBS)

run: all
	( cd $(OUT_DIR) && ./$(RUN_BNAME) ) #run from out dir

assembler: mkdir $(IN_DIR)$(ASSEMBLER_BASENAME)
	$(eval OPTIMIZE_FLAGS := -O0)
	$(CC) $(PROFILE_DEFINE) $(PROFILE_FLAGS) $(DEBUG_DEFINE) $(DEBUG_FLAGS) $(OPTIMIZE_FLAGS) $(CFLAGS) -S "$(IN_DIR)$(ASSEMBLE_BASENAME)" -o "$(OUT_DIR)$(ASSEMBLE_BASENAME).s"

debug: clean set_debug_flags all
	( cd $(OUT_DIR) && gdb "$(RUN_BNAME)" )

set_debug_flags:
	$(eval DEBUG_FLAGS := -ggdb3)
	$(eval DEBUG_DEFINE := -DDEBUG)
	$(eval OPTIMIZE_FLAGS := -O0)

profile: clean set_profile_flags all run
	( cd $(OUT_DIR) && gprof -b $(RUN_BNAME) gmon.out | tee "$(RUN_BNAME).profile_out" | less )

set_profile_flags:
	$(eval PROFILE_FLAGS := -p -pg)
	$(eval PROFILE_DEFINE := -DPROFILE)
	#$(eval OPTIMIZE_FLAGS := -O0)

clean:
	rm -rf "$(OUT_DIR)"
