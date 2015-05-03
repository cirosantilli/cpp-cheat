# glibc

1. [Source tree](source-tree.md)

## Introduction

glibc is GNU's implementation of:

- libc. By far the most popular implementation on Linux.
- POSIX C API
- glibc extensions such as interfaces to system calls

Project home: <http://www.gnu.org/software/libc/>

Documentation: <http://www.gnu.org/software/libc/manual/html_mono/libc.html>

This shall only document GNU extensions to libc in its implementation called glibc.

Extensions which are very thin interfaces to system calls will be documented together with system calls and not here.

POSIX C API shall not be discussed, only points which are specific to glibc shall be discussed here.

glibc does not necessarily come with GCC, the compiler: you could in theory choose between different implementations.

In Ubuntu 14.04:

-   headers for glibc are on `/usr/include`, e.g. `/usr/include/stdio.h`. Try: `locate /stdio.h`
-   lib for glibc are on `/usr/lib/i386-linux-gnu`. Try: `locate libc.so`. I have two `libc.so`:
    - `/lib/x86_64-linux-gnu/libc.so.6` from `libc6` package, which is used by other packages. The packages does not contain headers.
    - `/usr/lib/x86_64-linux-gnu/libc.so` from the `libc6-dev` package, which is used by things you compile yourself. The package also contains headers.
-   the Ubuntu package that contains it is called `libc6-dev`. See it with: `apt-file search `
