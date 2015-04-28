# glibc

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

## Source tree

    git clone git://sourceware.org/git/glibc.git
    mkdir glibc-build
    cd glibc-build
    bash ../glibc/configure --disable-sanity-checks
    make -j5

Took 4 minutes on a 2012 machine for version 2.21.

TODO every command I now run in the build directory tries to use the built libc in the current directory and segfaults. `echo $LD_LIBRARY_PATH` does not show the current directory, but doing `unset LD_LIBRARY_PATH` solves the problem. `mv libc.so.6 libc.so.6.bak` also works. TODO what to do?

-   `sysdeps`: contains multiple assembly and OS dependant optimized implementations of several functions, e.g. `sysdeps/x86_64/multiarch/memcmp-sse4.S`, `memcmp-ssse3.S`. Note the large specificity of the implementations.

    Each method also has a pure C implementation, e.g. `string/memcmp.c`, but that is likely to be much less efficient.
