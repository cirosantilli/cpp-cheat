BUILD_DIR := build/
TARGET    := qtcheat

run: all
	cd "$(BUILD_DIR)" && ./$(TARGET)

# Doing `qmake ../` is called a shadow build.
all:
	if [ ! -r qt.pro ]; then qmake -project; fi &&\
	mkdir -p "$(BUILD_DIR)" &&\
	cd "$(BUILD_DIR)" &&\
	qmake ../ &&\
	make

clean:
	rm -rf "$(BUILD_DIR)"

install: all
	cd "$(BUILD_DIR)" && sudo make install
	$(TARGET)

uninstall: all
	cd "$(BUILD_DIR)" && sudo make uninstall
	$(TARGET)
