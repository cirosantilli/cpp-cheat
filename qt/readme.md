On Linux:

- to build and run use `./make.sh`.
- to clean use `make distclean`.

Initial `qt.pro` template generated via `qmake -project`.

Initial `Makefile` template was generated via `qmake`.

Find Qt version:

    qmake --version

Sample output:

    QMake version 2.01a
    Using Qt version 4.8.4 in /usr/lib/i386-linux-gnu

QT adds new keywords to the C++ language such as `slots` and `emmit`.
Those are then translated into C++ before compilation.
This is a point that complicates QT learning.
*Never* use those keywords, or they will get preprocessed
and you will get weird errors!

Some objects cannot be created on the stack, only on the heap.
QT takes charge of their deletion when the time comes.

#sources

- <www.zetcode.com/gui/qt4/firstprograms/>

    Short but good tutorial.
