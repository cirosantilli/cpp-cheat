#compiles c files with gcc and c++ files with g++, one by one separatelly

CC := gcc
CXX := g++

CFLAGS := -Wall -Wno-unused-variable -Wno-unused-but-set-variable -std=c99
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
#override RUN?=c
override RUN?=func
#override RUN?=cpp

RUN_PATH:=$(OUT_DIR)$(RUN)$(OUT_EXT)

PROFILE_FLAGS:=
OPTIMIZE_FLAGS:=-O3

.PHONY: all mkdir clean profile set_profile_flags

all: mkdir $(C_OUTS) $(CPP_OUTS)

profile: clean set_profile_flags all run
	mv -f gmon.out $(OUT_DIR)
	gprof $(RUN_PATH) $(OUT_DIR)gmon.out

set_profile_flags:
	$(eval PROFILE_FLAGS := -p -pg)
	$(eval OPTIMIZE_FLAGS := )

run: all
	./$(RUN_PATH)
	
mkdir:
	mkdir -p "$(OUT_DIR)"

$(OUT_DIR)%$(OUT_EXT): $(IN_DIR)%.c
	$(CC) $(OPTIMIZE_FLAGS) $(PROFILE_FLAGS) $(CFLAGS) -o "$@" "$<" $(LIBS)

$(OUT_DIR)%$(OUT_EXT): $(IN_DIR)%.cpp
	$(CXX) $(OPTIMIZE_FLAGS) $(PROFILE_FLAGS) $(CXXFLAGS) -o "$@" "$<" $(LIBS)

clean:
	rm -rf "$(OUT_DIR)"
