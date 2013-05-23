OUT_DIR := _out/
OUT_EXT := .elf

.PHONY: clean run

$(OUT_DIR)posix$(OUT_EXT): posix.c
	mkdir -p _out/
	gcc -Wall -std=c99 -pedantic-errors -D_XOPEN_SOURCE=700 -o "$@" "$<"

run: $(OUT_DIR)posix$(OUT_EXT)
	cd $(OUT_DIR) && ./posix$(OUT_EXT) #run from out dir

clean:
	rm -rf $(OUT_DIR)
