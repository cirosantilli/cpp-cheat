# C++ Cheat

[![Build Status](https://travis-ci.org/cirosantilli/cpp-cheat.svg?branch=master)](https://travis-ci.org/cirosantilli/cpp-cheat)

C and C++ information, cheatsheets and mini-projects.

Relies on <https://github.com/cirosantilli/cpp-boilerplate> to factor code out. See [its documentation](https://github.com/cirosantilli/cpp-boilerplate/blob/master/README.md) for information on how to use this project.

## Most useful files

- [c.c](c.c): C cheatsheet
- [cpp.cpp](main_cpp.cpp): C++ cheatsheet
- [POSIX](posix/): POSIX C API
- [Multi-file](multifile/): `include`, `extern` vs `static`, dynamic libraries, cross language calls
- [GCC](gcc/): GCC extensions
- [OpenGL](opengl/)
- [KDE](kde/)

Other files:

- [Boost](boost/)
- [Flex and Bison](flex-bison/)
- [GDB](gdb.md)
- [glibc](glibc/)
- [Implementations](implementations.md)
- [Style guides](style-guides.md)
- [CMake](cmake.md)
- [hello_world.c](hello_world.c)
- [hello_world_cpp.cpp](hello_world_cpp.cpp)

GUI:

- [GTK](gtk/)
- [Qt](qt/)
- [X11](x11)
- [Open GL](opengl/)

Scientific:

- [Fortran](fortran/)
- [GSL](gsl/)
- [LAPACK](lapack/)
- [OpenCV](opencv/)
- [PLplot](plplot/)

## Dependencies

Most builds require:

- `make` (POSIX)
- `gcc` >= 4.7
- `g++` >= 4.7

Even though we use GNU tools by default, great attention is paid to portability of portable subjects like ANSI C, which should compile in any compiler.

In addition, each directory may have their own extra dependencies as stated in their README.

You can install dependencies on latest LTS Ubuntus with:

    ./configure

Other system install are not going to be supported as that would lead to too much maintenance overhead. If you don't have Ubuntu, consider using our [Vagrantfile](Vagrantfile).

## Usage

When there are multiple files compiled, e.g.:

    c.c -> c
    cpp.cpp -> cpp

run a given file by specifying the basename without extension:

    make run=c
    make run=cpp

The `=` sign is *not* optional!

Doing just `make run` in those cases will run the default file: `main`.

## Style

Non-portable features shall be clearly separated from portable ones in either:

- ifdef macro blocks
- separate files
- separate directories
- separate repositories

This includes features which were not present in the first standardized version of languages. E.g., C99 features must be put inside `#ifdf __STDC_VERSION__` blocks.

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

##
