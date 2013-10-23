BUILD_DIR := build/

run: all
	cd "$(BUILD_DIR)" && ./kdecheat

all:
	mkdir -p "$(BUILD_DIR)"
	cd "$(BUILD_DIR)" &&\
	cmake ../ &&\
	make

clean:
	rm -rf "$(BUILD_DIR)"

# It is necessary to install in order for certain features to apply,
# for example ui.rc files.
install: all
	cd "$(BUILD_DIR)" && sudo make install
	kdecheat

uninstall: all
	cd "$(BUILD_DIR)" && sudo make uninstall
