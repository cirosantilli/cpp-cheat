# C++ Cheat

This repo is moving to: https://github.com/cirosantilli/linux-kernel-module-cheat#userland-content

No major new features are intended to be added here.

This move unifies all my system programming content into one place, which makes it easier to maintain and discover, and immediately leads to more features being available due to better factoring, notably:

- run tests in parallel due to more flexible Python build system
- ability to build and run other CPU ISAs through emulation

This repo was written in a semi ad hoc way across several years, so it is a quality roller coaster, with old files crappy and new files less crappy. Only good or cleaned up examples will be migrated.

It is still early stages, and I'm not going to do the migration in one go now, but rather as I touch the examples.

However, since I use this repo often and give it a considerable importance, it is likely that everything that has value here will be moved sooner or later.

## Old README

[![Build Status](https://travis-ci.org/cirosantilli/cpp-cheat.svg?branch=master)](https://travis-ci.org/cirosantilli/cpp-cheat)

C, C++, POSIX and Linux system programming minimal examples. Asserts used wherever possible. Hello worlds for cool third party libraries and build systems. Cheatsheets, tutorials and mini-projects.

[Assembly Cheat](https://github.com/cirosantilli/assembly-cheat) contains lower level issues, like assembly, ELF and Binutils.

1.  [Getting started](getting-started.md)
1.  Featured
    1.  [C](c/)
    1.  [C++](cpp/)
    1.  [POSIX](posix/): POSIX C API
    1.  [OpenGL](opengl/)
    1.  [GCC](gcc/): GCC extensions
    1.  [Shared library](shared_library/)
1.  Cross-language
    1.  [C from C++](c_from_cpp/)
    1.  [C++ from C](cpp_from_c/)
    1.  [Fortran from C](fortran_from_c/)
    1.  [SWIG](swig/)
1.  Build systems
    1.  [make](make/)
    1.  [CMake](cmake/)
    1.  [SCons](scons/)
1.  Analysis tools
    1.  [GDB](gdb/)
1.  GCC
    1.  [GCC -std= default](gcc_std_default/)
    1.  GNU LD linker
        1.  [Incremental linking](linker/incremental_link/)
        1.  [Fixed variable address](linker/variable_address/)
        1.  [gold linker benchmark](linker/gold_benchmark/)
1.  Parsing
    1.  [Flex and Bison](flex_bison/)
1.  Media
    1.  [FFmpeg](ffmpeg/)
    1.  [libpng](png/)
    1.  [v4l2](v4l2/)
1.  Utility
    1.  [Boost](boost/)
    1.  [glibc](glibc/)
    1.  [Linux](linux/)
1.  GUI
    1.  [GTK](gtk/)
    1.  [KDE](kde/)
    1.  [OpenGL](opengl/)
    1.  [Qt](qt/)
    1.  [SDL](sdl/)
    1.  [X11](x11/)
        1.  [X11 hello world](x11/hello_world.c)
1.  Scientific
    1.  [Bullet physics](bullet/)
    1.  [CUDA](cuda/)
    1.  [Fortran](fortran/)
    1.  [GSL](gsl/)
    1.  [LAPACK](lapack/)
    1.  [OpenCL](opencl/)
    1.  [OpenCV](opencv/)
    1.  [PLplot](plplot/)
1.  [CONTRIBUTING](CONTRIBUTING.md)
