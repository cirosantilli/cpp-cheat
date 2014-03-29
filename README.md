C and C++ information, cheatsheets and mini-projects.

Based on Linux tools, but portable code is clearly separated from non-portable. Thoroughly tested on Ubuntu 12.04. Ports and reproduction reports on other systems are welcome.

# Most useful files

- [c.c](c.c): C cheatsheet.
- [cpp.cpp](main_cpp.cpp): C++ cheatsheet.
- `Makefile.*`: Makefiles that take care of a ton of possibilities.
- [opengl/](opengl/)
- [kde/](kde/)

# Quickstart

To compile and run each directory on Ubuntu 12.04 do:

    make install-ubuntu
    make run

You *must* run `make install-ubuntu` on the top-level before compiling any subdirectories, as this will install basic tools such as recent enough `gcc` and `g++` for C11 and C++11.

When there are multiple files compiled, e.g.:

    c.c -> c
    cpp.cpp -> cpp

run a given file by specifying the basename without extension:

    make run=c
    make run=cpp

The `=` sign is *not* optional!

Doing just `make run` in those cases will run the default file.

To print the generated assembly code to the screen use:

    make asm RUN=cpp

To get help on all options use:

    make help

# About

Larger projects may be in separate dirs.

There may be other compiled languages here for which we don't have much material for a separate dir, specially when we interface that language with C. Ex: Fortran.

Non-portable features shall be clearly separated from portable ones in either:

- ifdef blocks
- separate files
- separate directories
- separate repositories

Everything that can be checked in an assertion will be checked, and will not get printed.

For example, a C addition operator `+` test should be done as:

    assert(1 + 1 == 2);

and *never*:

    printf("%d\n", 1 + 1);

so that all can be verified automatically.

Features which yield unpredictable outputs can print results to stdout. For example, `time(NULL)`

    printf("%d\n", 1 + 1);

Features that:

- require user input such as C `scanf`
- make programs wait for perceptible amounts of time

shall be put inside a block analogous to a `if (0){ ... }` to be turned on only when users want to test those specific features.

Cheat source comments are written in markdown *indented by headers* and commented out.

Every important keyword that one might search for in the feature has a hash before it, e.g. `#function`, `#include`, `#printf`, etc.
