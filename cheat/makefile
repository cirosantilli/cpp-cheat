#compiles c files with gcc and c++ files with g++, one by one separatelly

CC = gcc
CXX = g++

CFLAGS = -Wall -Wno-unused-variable -Wno-unused-but-set-variable
CXXFLAGS = -Wall -Wno-unused-variable -Wno-unused-but-set-variable

LIBS=

IN_DIR=./
OUT_DIR=_out/
OUT_EXT=.out

INS:=$(wildcard $(IN_DIR)*.c)
INS_NODIR:=$(notdir $(INS))
OUTS_NODIR:=$(patsubst %.c,%$(OUT_EXT),$(INS_NODIR))
C_OUTS:=$(addprefix $(OUT_DIR),$(OUTS_NODIR))

INS:=$(wildcard $(IN_DIR)*.cpp)
INS_NODIR:=$(notdir $(INS))
OUTS_NODIR:=$(patsubst %.cpp,%$(OUT_EXT),$(INS_NODIR))
CPP_OUTS:=$(addprefix $(OUT_DIR),$(OUTS_NODIR))

.PHONY: all mkdir clean

all: mkdir $(C_OUTS) $(CPP_OUTS)

run: all
ifdef RUN
	./$(OUT_DIR)$(RUN)$(OUT_EXT) $(RUN_ARGS)
else
	#./$(OUT_DIR)c$(OUT_EXT) $(RUN_ARGS)
	./$(OUT_DIR)cpp$(OUT_EXT) $(RUN_ARGS)
	#./$(OUT_DIR)func$(OUT_EXT) $(RUN_ARGS)
	#./$(OUT_DIR)user_input$(OUT_EXT) $(RUN_ARGS)
endif

mkdir:
	mkdir -p "$(OUT_DIR)"

$(OUT_DIR)%$(OUT_EXT): $(IN_DIR)%.c
	$(CC) $(CFLAGS) -o "$@" "$<" $(LIBS)

$(OUT_DIR)%$(OUT_EXT): $(IN_DIR)%.cpp
	$(CXX) $(CXXFLAGS) -o "$@" "$<" $(LIBS)

clean:
	rm -rf "$(OUT_DIR)"
