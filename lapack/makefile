#compiles c files with gcc and c++ files with g++, one by one separatelly

#this is mostly for test purposes. see: ``makefile.individual_out_bins`` for a more complete makefile

#c/cpp
override CC				?= gcc
override CFLAGS		?= -Wall -std=c99 -pedantic-errors
override CXX			?= g++
override CXXFLAGS	?= -Wall -std=c++0x -pedantic-errors
override LIBS			?= -lm -lblas -l:liblapack.so.3
override DEFINES 	?= -DPOSIX

#fortran
override FF ?= gfortran
override FFLIBS ?= -l:lapack/liblapack.so
override FFLAGS ?= -Wall -march=native -std=f95 -pedantic-errors  

#paths
override IN_DIR 	?= ./
override OUT_DIR 	?= _out/
override OUT_EXT 	?= .out

#run
override RUN ?= c			#basename without extension of file to run

override ASSEMBLER_BASENAME ?= c.c
override ASSEMBLE_EXT 			?= .c
override DEBUG_DEFINE 			?=
override DEBUG_FLAGS  			?=
override PROFILE_DEFINE 		?= #-DDEBUG
override PROFILE_FLAGS  		?= #
override OPTIMIZE_FLAGS			?= #-O3

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
	#fotran:
		sudo aptitude install -y liblapack-dev
	#c:
		sudo aptitude install -y libblas3gf-dev

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
	$(eval override OPTIMIZE_FLAGS := -O0)
	$(CC) $(PROFILE_DEFINE) $(PROFILE_FLAGS) $(DEBUG_DEFINE) $(DEBUG_FLAGS) $(OPTIMIZE_FLAGS) $(CFLAGS) -S "$(IN_DIR)$(ASSEMBLE_BASENAME)" -o "$(OUT_DIR)$(ASSEMBLE_BASENAME).s"

debug: clean set_debug_flags all
	( cd $(OUT_DIR) && gdb "$(RUN_BNAME)" )

set_debug_flags:
	$(eval override DEBUG_FLAGS := -ggdb3)
	$(eval override DEBUG_DEFINE := -DDEBUG)
	$(eval override OPTIMIZE_FLAGS := -O0)

profile: clean set_profile_flags all run
	( cd $(OUT_DIR) && gprof -b $(RUN_BNAME) gmon.out | tee "$(RUN_BNAME).profile_out" | less )

set_profile_flags:
	$(eval override PROFILE_FLAGS := -p -pg)
	$(eval override PROFILE_DEFINE := -DPROFILE)
	#$(eval override OPTIMIZE_FLAGS := -O0)

clean:
	rm -rf "$(OUT_DIR)"
