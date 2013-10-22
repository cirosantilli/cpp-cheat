KDE is built on top of QT.

If factors out many parts of applications, such as GUI

#ui.rc file

Specifies GUI parts via an XML file.

This file is parsed whenever the application will be launched.

In this way, it is simple to reconfigure the application without recompiling.

The file must be installed to work: it is not enough to be on the same directory as the executable.
