#compiler options
override CC			:= gcc
override CFLAGS	?= -Wall -std=c99 -pedantic -Wno-unused-function 

#paths
override AUX_DIR 						?= _out/
override OBJ_EXT 						?= .o
override IN_DIR 						?= ./
override IN_EXTS 						?= .lex .c
override OUT_DIR 						?= $(AUX_DIR)
override OUT_EXT 						?= .elf
override OUT_BASENAME_NOEXT	?= a

INS 				:= $(foreach IN_EXT, $(IN_EXTS), $(wildcard $(IN_DIR)*$(IN_EXT)) )
INS_NODIR 	:= $(notdir $(INS))
OBJS_NODIR	:= $(filter %$(OBJ_EXT), $(foreach IN_EXT, $(IN_EXTS), $(patsubst %$(IN_EXT),%$(OBJ_EXT),$(INS_NODIR))))
OBJS				:= $(addprefix $(AUX_DIR), $(OBJS_NODIR))

OUT_BASENAME:= $(OUT_BASENAME_NOEXT)$(OUT_EXT)
OUT					:= $(OUT_DIR)$(OUT_BASENAME)

#bison generated header:
FLEX_C			:= $(addprefix $(AUX_DIR), $(notdir $(patsubst %.lex, %.c, $(wildcard $(IN_DIR)*.lex))))

.PHONY: all run test mkdir clean ubuntu_install_deps

all: mkdir $(OUT)

.SECONDARY: $(FLEX_C)

$(OUT): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(OUT) -lfl

$(AUX_DIR)%$(OBJ_EXT): $(IN_DIR)%.c
	$(CC) $(CFLAGS) -c "$<" -o "$@"

$(AUX_DIR)%$(OBJ_EXT): $(AUX_DIR)%.c
	$(CC) $(CFLAGS) -I. -c "$<" -o "$@"

$(AUX_DIR)%.c: $(IN_DIR)%.lex
	flex  -o "$(AUX_DIR)$*".c "$<"

clean:
	rm -rf "$(AUX_DIR)" "$(OUT_DIR)"

mkdir:
	mkdir -p "$(AUX_DIR)" "$(OUT_DIR)"

run: all
	( cd $(OUT_DIR) && ./$(OUT_BASENAME) $(RUN_ARGS) )

test: all
	python test.py "$(OUT)"

ubuntu_install_deps:
	sudo aptitude install -y flex bison
