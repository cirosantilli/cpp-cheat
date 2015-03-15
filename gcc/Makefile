MAIN ?= main
IN_EXT ?= c
OUT_EXT ?= out

IN := $(MAIN).$(IN_EXT)
OUT := $(MAIN).$(OUT_EXT)

.PROXY: clean run

$(OUT): $(IN)
	gcc --std=gnu99 -Wall -Wno-unused-variable -Wno-unused-but-set-variable -o '$(OUT)' '$(IN)'

clean:
	rm -f '$(OUT)'

run: $(OUT)
	./'$(OUT)'
