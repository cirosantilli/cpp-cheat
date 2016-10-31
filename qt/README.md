# QT

Initial `qt.pro` template generated with:

    qmake -project

Initial `Makefile` template was generated with:

    qmake

Find Qt version that will be linked against:

    qmake --version

Sample output:

    QMake version 2.01a
    Using Qt version 4.8.4 in /usr/lib/i386-linux-gnu

Find default for `qmake` variables values (depends on which platform it was compiled for):

    qmake -query "QT_INSTALL_PREFIX"

All key value pairs:

    qmake -query

QT adds new keywords to the C++ language such as `slots` and `emmit`. Those are then translated into C++ before compilation. This is a point that complicates QT learning. *Never* use those keywords, or they will get preprocessed and you will get weird errors!

Some objects cannot be created on the stack, only on the heap. QT takes charge of their deletion when the time comes.

## Sources

-   <http://www.zetcode.com/gui/qt4/firstprograms/>

    Short but good tutorial.

-   <http://doc.qt.digia.com/4.7/all-examples.html>

    The example list.

-   On Ubuntu, get the source code for many examples:

        sudo aptitude install -y qt4-demos
