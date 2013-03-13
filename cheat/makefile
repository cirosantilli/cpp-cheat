#compiles c files with gcc and c++ files with g++, one by one separatelly

CC := gcc
CXX := g++
FF := gfortran

CFLAGS := -Wall -Wno-unused-variable -Wno-unused-but-set-variable -march=native -std=c99 -pedantic-errors
CXXFLAGS := -pthread -Wall -Wno-unused-variable -Wno-unused-but-set-variable -march=native -std=c++0x -pedantic-errors
FFLAGS := -pthread -Wall -Wno-unused-variable -Wno-unused-but-set-variable -march=native -std=f95 -pedantic-errors  

LIBS:=

IN_DIR:=./
OUT_DIR:=_out/
OUT_EXT:=.out

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

override DEFINES=-DPOSIX

override ASSEMBLER_BASENAME?=c.c
#override ASSEMBLER_FILE?=cpp.cpp

override RUN?=c
#override RUN?=func
#override RUN?=cpp

override ASSEMBLE_EXT?=.c
#override ASSEMBLE_EXT?=.cpp

override DEBUG_DEFINE?=
override DEBUG_FLAGS?=
override PROFILE_DEFINE?=
override PROFILE_FLAGS?=

RUN_BNAME:=$(RUN)$(OUT_EXT)
RUN_PATH:=$(OUT_DIR)$(RUN_BNAME)
ASSEMBLE_BASENAME:=$(RUN)$(ASSEMBLE_EXT)

#override OPTIMIZE_FLAGS?=-O3
override OPTIMIZE_FLAGS?=
#dont opt for educative purposes

.PHONY: all mkdir clean profile set_profile_flags

all: mkdir $(C_OUTS) $(CPP_OUTS) $(F_OUTS)

assembler: mkdir $(IN_DIR)$(ASSEMBLER_BASENAME)
	$(eval override OPTIMIZE_FLAGS := -O0)
	$(CC) $(PROFILE_DEFINE) $(PROFILE_FLAGS) $(DEBUG_DEFINE) $(DEBUG_FLAGS) $(OPTIMIZE_FLAGS) $(CFLAGS) -S "$(IN_DIR)$(ASSEMBLE_BASENAME)" -o "$(OUT_DIR)$(ASSEMBLE_BASENAME).s"

debug: clean set_debug_flags all
	gdb "$(RUN_PATH)"

set_debug_flags:
	$(eval override DEBUG_FLAGS := -ggdb3)
	$(eval override DEBUG_DEFINE := -DDEBUG)
	$(eval override OPTIMIZE_FLAGS := -O0)

profile: clean set_profile_flags all run
	mv -f gmon.out $(OUT_DIR)
	gprof -b $(RUN_PATH) $(OUT_DIR)gmon.out | tee "$(RUN_PATH).profile_out" | less

set_profile_flags:
	$(eval override PROFILE_FLAGS := -p -pg)
	$(eval override PROFILE_DEFINE := -DPROFILE)
	#$(eval override OPTIMIZE_FLAGS := -O0)

run: all
	( cd $(OUT_DIR) && ./$(RUN_BNAME) ) #run on out dir

mkdir:
	mkdir -p "$(OUT_DIR)"

clean:
	rm -rf "$(OUT_DIR)"

$(OUT_DIR)%$(OUT_EXT): $(IN_DIR)%.c
	$(CC) $(DEFINES) $(PROFILE_DEFINE) $(PROFILE_FLAGS) $(DEBUG_DEFINE) $(DEBUG_FLAGS) $(OPTIMIZE_FLAGS) $(CFLAGS) -o "$@" "$<" $(LIBS)

$(OUT_DIR)%$(OUT_EXT): $(IN_DIR)%.cpp
	$(CXX) $(PROFILE_DEFINE) $(PROFILE_FLAGS) $(DEBUG_DEFINE) $(DEBUG_FLAGS) $(OPTIMIZE_FLAGS) $(CXXFLAGS) -o "$@" "$<" $(LIBS)

$(OUT_DIR)%$(OUT_EXT): $(IN_DIR)%.f
	$(FF) $(OPTIMIZE_FLAGS) $(FFLAGS) -o "$@" "$<" $(LIBS)
