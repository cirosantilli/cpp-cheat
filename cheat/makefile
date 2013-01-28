#compiles c files with gcc and c++ files with g++, one by one separatelly

CC := gcc
CXX := g++

CFLAGS := -Wall -Wno-unused-variable -Wno-unused-but-set-variable -std=c1x
CXXFLAGS := -Wall -Wno-unused-variable -Wno-unused-but-set-variable -std=c++0x

LIBS:=

IN_DIR:=./
OUT_DIR:=_out/
OUT_EXT:=.out

INS:=$(wildcard $(IN_DIR)*.c)
INS_NODIR:=$(notdir $(INS))
OUTS_NODIR:=$(patsubst %.c,%$(OUT_EXT),$(INS_NODIR))
C_OUTS:=$(addprefix $(OUT_DIR),$(OUTS_NODIR))

INS:=$(wildcard $(IN_DIR)*.cpp)
INS_NODIR:=$(notdir $(INS))
OUTS_NODIR:=$(patsubst %.cpp,%$(OUT_EXT),$(INS_NODIR))
CPP_OUTS:=$(addprefix $(OUT_DIR),$(OUTS_NODIR))

#default basename without extension to run if RUN not given
override RUN?=c
#override RUN?=func
#override RUN?=cpp
override DEBUG_DEFINE?=
override DEBUG_FLAGS?=
override PROFILE_DEFINE?=
override PROFILE_FLAGS?=

RUN_PATH:=$(OUT_DIR)$(RUN)$(OUT_EXT)

override OPTIMIZE_FLAGS?=-O3

.PHONY: all mkdir clean profile set_profile_flags

all: mkdir $(C_OUTS) $(CPP_OUTS)

debug: clean set_debug_flags all
	gdb $(RUN_PATH)

set_debug_flags:
	$(eval override DEBUG_FLAGS := -ggdb3)
	$(eval override DEBUG_DEFINE := -DDEBUG)
	$(eval override OPTIMIZE_FLAGS := -O0)

profile: clean set_profile_flags all run
	mv -f gmon.out $(OUT_DIR)
	gprof -b $(RUN_PATH) $(OUT_DIR)gmon.out

set_profile_flags:
	$(eval override PROFILE_FLAGS := -p -pg)
	$(eval override PROFILE_DEFINE := -DPROFILE)
	$(eval override OPTIMIZE_FLAGS := -O0)

run: all
	./$(RUN_PATH)
	
mkdir:
	mkdir -p "$(OUT_DIR)"

$(OUT_DIR)%$(OUT_EXT): $(IN_DIR)%.c
	$(CC) $(PROFILE_DEFINE) $(PROFILE_FLAGS) $(DEBUG_DEFINE) $(DEBUG_FLAGS) $(OPTIMIZE_FLAGS) $(CFLAGS) -o "$@" "$<" $(LIBS)

$(OUT_DIR)%$(OUT_EXT): $(IN_DIR)%.cpp
	$(CXX) $(PROFILE_DEFINE) $(PROFILE_FLAGS) $(DEBUG_DEFINE) $(DEBUG_FLAGS) $(OPTIMIZE_FLAGS) $(CXXFLAGS) -o "$@" "$<" $(LIBS)

clean:
	rm -rf "$(OUT_DIR)"
