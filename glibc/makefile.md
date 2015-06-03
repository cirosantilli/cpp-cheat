# Makefile

Build:

    mkdir glibc
    git clone git://sourceware.org/git/glibc.git src
    mkdir build
    cd build
    # TODO better way? Why is this needed?
    unset LD_LIBRARY_PATH
    ../src/configure --prefix="$(pwd)/../install"
    time make -j5

Took 4 minutes on a 2012 machine for version 2.21.

TODO every command I now run from the build directory tries to use the built libc in the current directory and segfaults. `echo $LD_LIBRARY_PATH` does not show the current directory, but doing `unset LD_LIBRARY_PATH` solves the problem, why?. `mv libc.so.6 libc.so.6.bak` also works.

Interesting installed files:

- `/bin/ldd`
