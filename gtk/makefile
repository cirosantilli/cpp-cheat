#compiles c files with gcc and c++ files with g++, one by one separatelly

CC := gcc
CXX := g++

PKGNAME=gtk+-3.0

CFLAGS := $(shell pkg-config --cflags "$(PKGNAME)")
CXXFLAGS := -Wall -march=native -std=c++0x -pedantic-errors

LIBS := $(shell pkg-config --libs "$(PKGNAME)")

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

DEFINES=

ASSEMBLER_BASENAME?=c.c
ASSEMBLER_FILE?=cpp.cpp

RUN?=min

ASSEMBLE_EXT?=.c
ASSEMBLE_EXT?=.cpp

DEBUG_DEFINE?=
DEBUG_FLAGS?=
PROFILE_DEFINE?=
PROFILE_FLAGS?=

RUN_PATH:=$(OUT_DIR)$(RUN)$(OUT_EXT)
ASSEMBLE_BASENAME:=$(RUN)$(ASSEMBLE_EXT)

OPTIMIZE_FLAGS?=-O3
OPTIMIZE_FLAGS?=
#dont opt for educative purposes

.PHONY: all mkdir clean profile set_profile_flags install-deps-ubuntu

all: mkdir $(C_OUTS) $(CPP_OUTS)

assembler: mkdir $(IN_DIR)$(ASSEMBLER_BASENAME)
	$(eval OPTIMIZE_FLAGS := -O0)
	$(CC) $(PROFILE_DEFINE) $(PROFILE_FLAGS) $(DEBUG_DEFINE) $(DEBUG_FLAGS) $(OPTIMIZE_FLAGS) $(CFLAGS) -S "$(IN_DIR)$(ASSEMBLE_BASENAME)" -o "$(OUT_DIR)$(ASSEMBLE_BASENAME).s"

debug: clean set_debug_flags all
	gdb "$(RUN_PATH)"

set_debug_flags:
	$(eval DEBUG_FLAGS := -ggdb3)
	$(eval DEBUG_DEFINE := -DDEBUG)
	$(eval OPTIMIZE_FLAGS := -O0)

profile: clean set_profile_flags all run
	mv -f gmon.out $(OUT_DIR)
	gprof -b $(RUN_PATH) $(OUT_DIR)gmon.out | tee "$(RUN_PATH).profile_out" | less

set_profile_flags:
	$(eval PROFILE_FLAGS := -p -pg)
	$(eval PROFILE_DEFINE := -DPROFILE)
	#$(eval OPTIMIZE_FLAGS := -O0)

run: all
	./$(RUN_PATH)

mkdir:
	mkdir -p "$(OUT_DIR)"

clean:
	rm -rf "$(OUT_DIR)"

install-deps-ubuntu:
	sudo apt-get install -y libgtk-3-dev

$(OUT_DIR)%$(OUT_EXT): $(IN_DIR)%.c
	$(CC) $(DEFINES) $(PROFILE_DEFINE) $(PROFILE_FLAGS) $(DEBUG_DEFINE) $(DEBUG_FLAGS) $(OPTIMIZE_FLAGS) $(CFLAGS) -o "$@" "$<" $(LIBS)

$(OUT_DIR)%$(OUT_EXT): $(IN_DIR)%.cpp
	$(CXX) $(PROFILE_DEFINE) $(PROFILE_FLAGS) $(DEBUG_DEFINE) $(DEBUG_FLAGS) $(OPTIMIZE_FLAGS) $(CXXFLAGS) -o "$@" "$<" $(LIBS)
