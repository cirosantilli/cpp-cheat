BUILD_DIR := build/
TARGET    := qtcheat

# Doing `qmake ../` is called a shadow build.
all:
	if [ ! -r qt.pro ]; then qmake -project; fi &&\
	mkdir -p "$(BUILD_DIR)" &&\
	cd "$(BUILD_DIR)" &&\
	qmake ../ &&\
	make

clean:
	rm -rf "$(BUILD_DIR)"

run: all
	cd "$(BUILD_DIR)" && ./$(TARGET)

install: all
	cd "$(BUILD_DIR)" && make install

install-run:
	$(TARGET)

deps:
	sudo aptitude update
	sudo aptitude install -y libqt4-dev

uninstall: all
	cd "$(BUILD_DIR)" && make uninstall
	$(TARGET)
