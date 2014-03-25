Simple C and C++ programs, cheats and mini projects.

The most useful sections are currently:

- [c/c.c](c/c.c): C cheatsheet.
- [c/cpp.cpp](c/cpp.cpp): C++ cheatsheet.
- `makefile.*`: makefiles that take care of a ton of possibilities.

Other reasonably useful cheats can be found under:

- [opengl/](opengl/)
- [kde/](kde/)

# Install on Linux

Most systems already have GCC installed, however some of this relies on the recent GCC 4.7 to be able to try out bleeding edge c11.

This is not recommended for production.

On Ubuntu 12.04, install GCC 4.8 with:

    sudo add-apt-repository ppa:ubuntu-toolchain-r/test
    sudo aptitude install -y update
    sudo aptitude install gcc-4.8
    sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.8 50

# About

Currently uses Linux tools, but Windows ports are welcome.

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
