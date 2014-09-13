# glibc

glibc is GNU's implementation of:

- libc. By far the most popular implementation on Linux.
- POSIX C API
- glibc extensions such as interfaces to system calls

This shall only document GNU extensions to libc in its implementation called glibc.

Extensions which are very thin interfaces to system calls will be documented together with system calls and not here.

POSIX C API shall not be discussed, only points which are specific to glibc shall be discussed here.

Official documentation: <http://www.gnu.org/software/libc/manual/html_mono/libc.html>

glibc does not necessarily come with GCC, the compiler: you could in theory choose between different implementations.

In Ubuntu

- headers for glibc are on `/usr/include`. Try: `locate /stdio.h`
- lib for glibc are on `/usr/lib/i386-linux-gnu`. Try: `locate /libc.a`
- the Ubuntu package that contains it is called `libc6-dev`. See it with: `dpkg -l | grep libc`
