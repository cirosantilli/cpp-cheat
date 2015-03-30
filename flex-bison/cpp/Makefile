#makes all input files in the current dir ( given by the input extension IN_EXTS)
#into objects, and compiles all objects into an executable.

#as usual, .l and .y are first used to generate .c and only then into objects.

#basenames without extensions are always kept and must be unique across extensions.
#Example: `a.y` will become `a.o`, and `a.c` will also become `a.o`, so you can't
#have both those files in the same project!

#compiler options
CC			:= g++
CFLAGS	?= -Wall -std=c++0x -pedantic

#paths
AUX_DIR 						?= _build/
OBJ_EXT 						?= .o
IN_DIR 						?= ./
FLEX_EXT  				  ?= .l
BISON_EXT  				?= .y
IN_EXTS 						?= $(FLEX_EXT) $(BISON_EXT) .c .cpp
OUT_DIR 						?= $(AUX_DIR)
OUT_EXT 						?= .elf
OUT_BASENAME_NOEXT	?= a

INS 				:= $(foreach IN_EXT, $(IN_EXTS), $(wildcard $(IN_DIR)*$(IN_EXT)) )
INS_NODIR 	:= $(notdir $(INS))
OBJS_NODIR	:= $(filter %$(OBJ_EXT), $(foreach IN_EXT, $(IN_EXTS), $(patsubst %$(IN_EXT),%$(OBJ_EXT),$(INS_NODIR))))
OBJS				:= $(addprefix $(AUX_DIR), $(OBJS_NODIR))

OUT_BASENAME:= $(OUT_BASENAME_NOEXT)$(OUT_EXT)
OUT					:= $(OUT_DIR)$(OUT_BASENAME)

#bison generated header:
BISON_H			:= $(addprefix $(AUX_DIR), $(notdir $(patsubst %$(BISON_EXT), %.h, $(wildcard $(IN_DIR)*$(BISON_EXT)))))
FLEX_C			:= $(addprefix $(AUX_DIR), $(notdir $(patsubst %$(FLEX_EXT), %.c, $(wildcard $(IN_DIR)*$(FLEX_EXT)))))

.PHONY: all clean mkdir run test

.SECONDARY: $(FLEX_C) $(BISON_H)

#must turn off possible implicit l y rules!!!
.SUFFIXES:

all: mkdir $(OUT)

$(OUT): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(OUT) -lfl

$(AUX_DIR)%$(OBJ_EXT): $(IN_DIR)%.c $(BISON_H)
	$(CC) $(CFLAGS) -c "$<" -o "$@"

$(AUX_DIR)%$(OBJ_EXT): $(IN_DIR)%.cpp $(BISON_H)
	$(CC) $(CFLAGS) -c "$<" -o "$@"

$(AUX_DIR)%$(OBJ_EXT): $(AUX_DIR)%.c $(BISON_H)
	$(CC) $(CFLAGS) -I. -c "$<" -o "$@"

$(AUX_DIR)%.c: $(IN_DIR)%$(FLEX_EXT)
	flex -o "$(AUX_DIR)$*".c "$<"

$(AUX_DIR)%.c $(AUX_DIR)%.h: $(IN_DIR)%$(BISON_EXT)
	bison -v -o "$(AUX_DIR)$*".c --defines="$(AUX_DIR)$*".h "$<"

clean:
	rm -rf "$(AUX_DIR)" "$(OUT_DIR)"

mkdir:
	mkdir -p "$(AUX_DIR)" "$(OUT_DIR)"

run: all
	( cd $(OUT_DIR) && ./$(OUT_BASENAME) $(RUN_ARGS) )

test: all
	./test "$(OUT_DIR)" $(OUT_BASENAME)
