# Introduction

GCC is arguably the most popular C and C++ compiler.

GCC stands for GNU Compiler Collection: *not* C compiler, and currently compiles: C, C++, Objective-C, Fortran, Java, Ada, and Go.

The Linux kernel uses GCC extensions so you need it to build it.

`gcc` is the C compiler. It is a large frontend for other tools such as `as`, `cpp`.

`gcc` and `g++` are the dominant compilers on Linux. Important alternatives include `clang` and Intel's `icc`.

Only *language* extension are discussed: glibc extensions are not. Language extensions are documented at: <https://gcc.gnu.org/onlinedocs/gcc/C-Extensions.html>

You can disable all non-GNU specific languages features with flags like `-ansi or -std=c99`, which you should always do. This will not however stop defining certain GNU specific preprocessor macros such as `__GNUC__`

Obviously, it is always better if you avoid using extensions, but you may encounter them in Linux specific projects, such as the Linux kernel itself for example.

GNU extensions have a large chance of being implemented in future ANSI C versions (but sometimes in a modified form) because of the large influence of GCC.

## g++ vs gcc

`g++`: <http://stackoverflow.com/questions/172587/what-is-the-difference-between-g-and-gcc>

Most important differences:

- `g++` treats both `.c` and `.cpp` files as C++, since `.c` is backwards compatible with C++, it works
- `g++` links to (but does not include) stdlib automatically, `gcc` does not!

## Supported executable formats

Major ones:

- ELF (Linux)
- Mach-O (Mac OS)
- PE (Windows)

but there are others.

## What languages it compiles

GCC has front-ends and back-ends:

- front-ends: input languages
- back-ends: output machine codes

Infrastructure is reused across multiple languages.

Front-ends for which GCC is the major Linux implementation: C, C++, Fortran, Ada.

Other front-ends:

- Java (deprecated), Oracle's `javac`
- Go, Google's `gc`
- Objective-C: TODO. What does Apple use? There is also a LLVM

GCC also offers standard libraries for most languages it supports, except `libc`, which is in the separate project `glibc`, which is highly optimized, and has per-processor implementations.
