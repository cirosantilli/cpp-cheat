TEMPLATE    = app

# Executable name:
TARGET      = qtcheat

DEPENDPATH  += .
INCLUDEPATH += .

# Input source files:
SOURCES     += main.cpp

# Input Qt Designer ui files:
FORMS       = qt_designer.ui

# Input header files:
HEADERS     += SlotTest.h

# Will only execute in POSIX systems (includes MAC OS):
# TODO generated makefile uninstall attempts to remove the intall dir(/usr/local/bin). How to prevent that?
# TODO how to install the icons / resources? How to run tests with them?
unix {
    target.path = /usr/local/bin
    INSTALLS    += target
}
