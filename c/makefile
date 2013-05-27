#compiles c files with gcc and c++ files with g++, fortran with gfortran one by one separatelly

#c/cpp
override CC ?= gcc
override CXX ?= g++
override CFLAGS ?= -Wall -std=c99 -pedantic-errors -Wno-unused-variable -Wno-unused-but-set-variable 
override CXXFLAGS ?= -pthread -Wall -std=c++0x -pedantic-errors -Wno-unused-variable -Wno-unused-but-set-variable 
override LIBS ?=

#fortran
override FF ?= gfortran
override FFLIBS ?= -l:lapack/liblapack.so
override FFLAGS ?= -Wall -march=native -std=f2003 -pedantic-errors -Wno-unused-variable -Wno-unused-but-set-variable 

#paths
override IN_DIR ?= ./
override IN_EXTS ?= .c .cpp .f
override OUT_DIR ?= _out/
override OUT_EXT ?= .out

override DEFINES ?=
override ASSEMBLER_BASENAME? = c.c
#override ASSEMBLER_FILE?=cpp.cpp

override RUN ?= c
#override RUN?=func
#override RUN?=cpp

override ASSEMBLE_EXT ?= .c
#override ASSEMBLE_EXT?=.cpp

override DEBUG_DEFINE ?=
override DEBUG_FLAGS ?=
override PROFILE_DEFINE ?=
override PROFILE_FLAGS ?=
#override OPTIMIZE_FLAGS?=-O3
override OPTIMIZE_FLAGS?=

INS			:= $(foreach IN_EXT, $(IN_EXTS), $(wildcard $(IN_DIR)*$(IN_EXT)) )
INS_NODIR 	:= $(notdir $(INS))
OUTS_NODIR	:= $(shell for f in $(INS_NODIR); do echo -n "$${f%.*} "; done )
OUTS_NODIR	:= $(addsuffix $(OUT_EXT), $(OUTS_NODIR) )
OUTS		:= $(addprefix $(OUT_DIR), $(OUTS_NODIR))

RUN_BNAME:=$(RUN)$(OUT_EXT)
RUN_PATH:=$(OUT_DIR)$(RUN_BNAME)
ASSEMBLE_BASENAME:=$(RUN)$(ASSEMBLE_EXT)

.PHONY: all mkdir clean profile set_profile_flags get_outdir

all: mkdir $(OUTS)

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
	( cd $(OUT_DIR) && ./$(RUN_BNAME) ) #run from out dir

mkdir:
	mkdir -p "$(OUT_DIR)"

clean:
	rm -rf "$(OUT_DIR)"

$(OUT_DIR)%$(OUT_EXT): $(IN_DIR)%.c
	$(CC) $(DEFINES) $(PROFILE_DEFINE) $(PROFILE_FLAGS) $(DEBUG_DEFINE) $(DEBUG_FLAGS) $(OPTIMIZE_FLAGS) $(CFLAGS) -o "$@" "$<" $(LIBS)

$(OUT_DIR)%$(OUT_EXT): $(IN_DIR)%.cpp
	$(CXX) $(PROFILE_DEFINE) $(PROFILE_FLAGS) $(DEBUG_DEFINE) $(DEBUG_FLAGS) $(OPTIMIZE_FLAGS) $(CXXFLAGS) -o "$@" "$<" $(LIBS)

$(OUT_DIR)%$(OUT_EXT): $(IN_DIR)%.f
	$(FF) $(OPTIMIZE_FLAGS) $(FFLAGS) -o "$@" "$<" $(FFLIBS)
