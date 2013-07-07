#compiles c files with gcc and c++ files with g++, fortran with gfortran one by one separatelly

#c/cpp
CC ?= gcc
CXX ?= g++
CFLAGS ?= -Wall -std=c99 -pedantic-errors -Wno-unused-variable -Wno-unused-but-set-variable
CXXFLAGS ?= -pthread -Wall -std=c++0x -pedantic-errors -Wno-unused-variable -Wno-unused-but-set-variable
LIBS ?=

#fortran
FF ?= gfortran
FFLIBS ?=
FFLAGS ?= -Wall -march=native -std=f2003 -pedantic-errors -Wno-unused-variable -Wno-unused-but-set-variable

#paths
IN_DIR ?= ./
IN_EXTS ?= .c .cpp .f
OUT_DIR ?= _out/
OUT_EXT ?=

DEFINES ?=
ASSEMBLER_BASENAME? = c.c
ASSEMBLER_FILE?=cpp.cpp

RUN ?= c
RUN?=func
RUN?=cpp

ASSEMBLE_EXT ?= .c
ASSEMBLE_EXT?=.cpp

DEBUG_DEFINE ?=
DEBUG_FLAGS ?=
PROFILE_DEFINE ?=
PROFILE_FLAGS ?=
OPTIMIZE_FLAGS?=-O3
OPTIMIZE_FLAGS?=

INS		:= $(foreach IN_EXT, $(IN_EXTS), $(wildcard $(IN_DIR)*$(IN_EXT)))
INS_NODIR 	:= $(notdir $(INS))
OUTS_NODIR	:= $(basename $(INS_NODIR))
OUTS_NODIR	:= $(addsuffix $(OUT_EXT), $(OUTS_NODIR))
OUTS		:= $(addprefix $(OUT_DIR), $(OUTS_NODIR))

RUN_BNAME	:= $(RUN)$(OUT_EXT)
RUN_PATH	:= $(OUT_DIR)$(RUN_BNAME)
ASSEMBLE_BASENAME	:= $(RUN)$(ASSEMBLE_EXT)

.PHONY: all clean get_outdir install-deps-ubuntu mkdir profile set_profile_flags testall

all: mkdir $(OUTS)

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
	cd $(OUT_DIR) && ./$(RUN_BNAME)

testall: all
	cd $(OUT_DIR) && set -e && for OUT in $(OUTS_NODIR); do ./$$OUT; done
	@echo "All tests passed."

mkdir:
	mkdir -p "$(OUT_DIR)"

clean:
	rm -rf "$(OUT_DIR)"

install-deps-ubuntu:
	sudo apt-get install g++
	sudo apt-get install gfortran

$(OUT_DIR)%$(OUT_EXT): $(IN_DIR)%.c
	$(CC) $(DEFINES) $(PROFILE_DEFINE) $(PROFILE_FLAGS) $(DEBUG_DEFINE) $(DEBUG_FLAGS) $(OPTIMIZE_FLAGS) $(CFLAGS) -o "$@" "$<" $(LIBS)

$(OUT_DIR)%$(OUT_EXT): $(IN_DIR)%.cpp
	$(CXX) $(PROFILE_DEFINE) $(PROFILE_FLAGS) $(DEBUG_DEFINE) $(DEBUG_FLAGS) $(OPTIMIZE_FLAGS) $(CXXFLAGS) -o "$@" "$<" $(LIBS)

$(OUT_DIR)%$(OUT_EXT): $(IN_DIR)%.f
	$(FF) $(OPTIMIZE_FLAGS) $(FFLAGS) -o "$@" "$<" $(FFLIBS)
