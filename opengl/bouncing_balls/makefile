CC		:= g++
LIBS 	:= -lm -lGL -lGLU -lglut

IN_EXT 	:= .cpp
IN_DIR 	:= ./
OUT_DIR := _out/
OUT_EXT :=

INS 		:= $(wildcard $(IN_DIR)*$(IN_EXT))
INS_NODIR 	:= $(notdir $(INS))
OUTS_NODIR 	:= $(patsubst %$(IN_EXT),%$(OUT_EXT),$(INS_NODIR))
OUTS 		:= $(addprefix $(OUT_DIR),$(OUTS_NODIR))

#RUN := one_ball
RUN := multi_ball

.PHONY: all mkdir clean

all: mkdir $(OUTS)

$(OUT_DIR)%$(OUT_EXT): $(IN_DIR)%$(IN_EXT)
	$(CC) -o "$@" "$<" $(LIBS)

clean:
	rm -rf $(OUT_DIR) $(AUX_DIR)

mkdir:
	mkdir -p "$(OUT_DIR)"

run: all
	cd $(OUT_DIR) && ./$(RUN)$(OUT_EXT)
