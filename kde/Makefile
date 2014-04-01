BUILD_DIR := build/
TARGET    := kdecheat

all:
	mkdir -p "$(BUILD_DIR)"
	cd "$(BUILD_DIR)" &&\
	cmake ../ &&\
	make

clean:
	rm -rf "$(BUILD_DIR)"

install: all
	cd "$(BUILD_DIR)" && make install

run: all
	cd "$(BUILD_DIR)" && ./$(TARGET)

# Run the installed version of the app in PATH.
# This does not automatically install because install is usually run as sudo,
# and it may be a bad idea to run the program as sudo.
run-install:
	$(TARGET)

uninstall: all
	cd "$(BUILD_DIR)" && make uninstall
