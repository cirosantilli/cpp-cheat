# Implementations

## Compilers

Most of those compilers work for multiple related languages such as C, C++, etc.:

[GCC](gcc/) is arguably the most popular implementation.

### clang

LLVM.

### icc

Intel.

Has intrinsics for every Intel instruction, and optimizes assembly really well for Intel. 

Closed source...

### CompCert C compiler

<http://compcert.inria.fr/compcert-C.html>

<https://github.com/AbsInt/CompCert>

INRIA formally verified compiler to a very large subset of C99.

Written and verified in Coq.

## libc

- glibc: GNU implementation, major on Linux
- Apple's libc is not glibc, but is open source <http://stackoverflow.com/questions/7592069/how-to-build-apples-opensource-libc>
- Microsoft likely has a closed source implementation

Then there are several implementations that target Linux-only embedded systems, and can therefore be smaller or more efficient:

- musl libc. Comparison: <http://www.etalabs.net/compare_libcs.html>. Alpine Linux moved to it, as it is partially binary compatible with glibc.
- Bionic (Android): <https://en.wikipedia.org/wiki/Bionic_%28software%29>
- dietlibc <http://www.fefe.de/dietlibc/>

### ulibc

<http://uclibc.org>

Stands for Micro libc.

Attempts to be very small for embedded systems.

One of the ways in which it is smaller is that it is Linux-only.

Was used in Alpine, but replaced with musl, which is partially binary compatible with glibc.
