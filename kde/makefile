BUILD_DIR := build/
TARGET    := kdecheat

all:
	mkdir -p "$(BUILD_DIR)"
	cd "$(BUILD_DIR)" &&\
	cmake ../ &&\
	make

run: all
	cd "$(BUILD_DIR)" && ./$(TARGET)

clean:
	rm -rf "$(BUILD_DIR)"

# It is necessary to install in order for certain features to apply,
# for example ui.rc files.
install: all
	cd "$(BUILD_DIR)" && make install

# This does not require install because install is usually run as sudo,
# and it may be a bad idea to run the program as sudo.
install-run:
	$(TARGET)

uninstall: all
	cd "$(BUILD_DIR)" && make uninstall
