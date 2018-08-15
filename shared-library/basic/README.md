# Basic

Basic example. Creates a shared and a static library from `a.c` and `b.c`, and uses them in the following ways:

Static library:

    ./maina.out

Dynamic library with relative `.so` path:

    LD_LIBRARY_PATH=. ./mainso.out

Requires `LD_LIBRARY_PATH=.` because we only store the basename of the `.so` in that executable.

Dynamic library with absolute `.so` path:

    ./mainso_fullpath.out
