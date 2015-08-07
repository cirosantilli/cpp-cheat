# Source tree

Tested on version 5.1.

## What GCC is coded with

Was C, then in 2012 at 4.8 started allowing C++.

There are however no `.cpp` or `.hpp` files: `.c` and `.hpp` extensions were kept.

## Programs

The single source tree contains:

- C, C++, etc. compilers
- Binutils: `as`, `ln`, `nm`

## Overview

The top 20 directories by size are:

    1.6G    .git
    360M    gcc
    165M    libjava
    78M     libstdc++-v3
    15M     libgo
    15M     libgcc
    14M     gmp-4.3.2
    8.0M    libgfortran
    7.4M    mpfr-2.4.2
    3.5M    zlib
    3.5M    libcpp
    3.1M    libgomp
    3.1M    boehm-gc
    3.0M    libffi
    2.9M    mpc-0.8.1
    2.5M    libiberty
    1.9M    libsanitizer
    1.7M    libquadmath
    1.5M    libitm
    1.5M    libdecnumber

The main source is under `gcc`:

    175M    testsuite
    49M     ada
    32M     config
    31M     po
    7.8M    cp
    6.4M    fortran
    5.1M    doc
    2.0M    go
    1.9M    java
    1.8M    ChangeLog-2004
    1.5M    ChangeLog-2011
    1.5M    ChangeLog-2010
    1.4M    ChangeLog-2005
    1.4M    ChangeLog-2003
    1.3M    ChangeLog-2012
    1.3M    ChangeLog-2009
    1.3M    ChangeLog-2007
    1.3M    ChangeLog-2002
    1.2M    ChangeLog-2001
    1.2M    ChangeLog-2000
    1.1M    c-family
    1.1M    c
    1.1M    ChangeLog-2008
    876K    ChangeLog-2006
    872K    objc
    836K    configure
    784K    ChangeLog-1999
    744K    ChangeLog.tree-ssa
    716K    dwarf2out.c
    640K    ChangeLog-1998
    552K    FSFChangeLog.11
    536K    fold-const.c

## Entry points

Under `gcc/`:

- `gcc-main.c`: `gcc`. Immediately forwards to `gcc.c driver::main`.
- `main.c`: `cc1`. Immediately forwards to `toplev.c toplev::main`.
- `collect2.c`

## Files

### collect2

TODO vs `ld`?

<https://gcc.gnu.org/onlinedocs/gcc-4.3.5/gccint/Collect2.html>

### cp

C++ specifics.

### lto

Link Time Optimization.

## C family

## c-family

C-family includes: C, C++, Objective C.

## gcc/doc/gccint.texi

Internals documentation, yay! <https://gcc.gnu.org/onlinedocs/gccint/index.html>

## Parser location

<http://stackoverflow.com/questions/2721071/c-grammar-in-gcc-source-code>

In the past long ago C used an explicit grammar and Bison.

4.8 just parses manually with:

    gcc/c/c-parser.c

and neighbours. A 10k LOC files.

## Built files

## Generated build files

### gcc

### xgcc

By default, `xgcc` is generated, and installed as `gcc`.

The `x` stands for Cross compiler.

### gcc-ar

### gcc-nm

### gcc-ranlib

Wrappers for LTO support.

<https://gcc.gnu.org/ml/gcc-help/2012-03/msg00100.html>

### libstdc++ location

Where did it go? Installation did install it however.

## libstdc++

TODO is this the most popular C++ stdlib implementation?

Unlike `glibc`, it has no per-architecture optimizations. Likely glibc provides the hardcore layer, and C++ the boilerplate layer.

## Register allocation

One of the hardest compiler problems, as it comes down to an NP complete graph coloring optimization.

Used to be done by the reload system, which was present from day 1, <https://gcc.gnu.org/wiki/reload>, but got replaced in 2012 by LRA by Red Hat: <ftp://gcc.gnu.org/pub/gcc/summit/2003/Graph%20Coloring%20Register%20Allocation.pdf> because reload was very unmaintainable.

On 5.1, `lra.c` is the main entry point, and has a nice block diagram documentation. The graph coloring algorithm is Chaitin-Briggs <http://stackoverflow.com/questions/14399608/chaitin-briggs-algorithm-explanation>

## include

Shared includes.

Many used in GCC and `libiberty`.

## libiberty

Shared GNU utilities.

Used by both GCC and Binutils, although it does not have it's own versioning.

## boehm-gc

<http://en.wikipedia.org/wiki/Boehm_garbage_collector>

Made available in the `gc.h` header through functions and macros of form `GC_malloc`

Doc: <http://linux.die.net/man/3/gc>

## libcilkrts

<http://en.wikipedia.org/wiki/Cilk>

## libsan

## libsanitizer

Static analysis, originally by Google:

- `asan`: address <http://code.google.com/p/address-sanitizer>
- `lsan`: leak
- `tsan` thread <http://code.google.com/p/thread-sanitizer/>
- `ubsan`: undefined behaviour

Activated by the `-fsanitize=` options.

Built as a dynamic library.

## libssp

Stack Smashing Protection:

- <http://aconole.brad-x.com/papers/exploits/ssp/intro>
- <http://en.wikipedia.org/wiki/Buffer_overflow_protection>

Security feature.

Built as a dynamic library.

## libvtv

Virtual table verification:

- <https://gcc.gnu.org/wiki/vtv>
- <https://sunglint.wordpress.com/2013/06/13/vtv/>

Security feature.

Built as a dynamic library.

## libcc1

TODO?

Exposes GCC compilation internals as a library?

Used by GDB's `compile` command.

Is a GCC plugin, that is how it accesses GCC.

## libmpx

Memory Protection Extensions. TODO?

## liboffloadmic

Intel MIC (many integrated cores architecture) offloading architecture support.

Looks a lot like a GPU, notably implemented on the Xeon Phi co-processor (4k USD) which was used for the fastest 2014 supercomputer Tianhe-2. The US government rejected Intel's export license when China wanted to increase it's capabilities further.

To offload means to pass work to it, and Itel claims this can be done intelligently from standard C code without developer effort?

- <https://en.wikipedia.org/wiki/Xeon_Phi>
- <https://software.intel.com/en-us/articles/effective-use-of-the-intel-compilers-offload-features>
- <http://www.intel.com/content/www/us/en/architecture-and-technology/many-integrated-core/intel-many-integrated-core-architecture.html>
- <http://goparallel.sourceforge.net/xeon-phi-vs-gpu-programming-better/>

## libitm

Transaction memory: <https://gcc.gnu.org/wiki/TransactionalMemory>

TODO why `i`?

## intl

Internationalization, taken from `gettext`, and upstreamed there.

## libffi

Foreign Function Interface.

<https://sourceware.org/libffi/>

<https://en.wikipedia.org/wiki/Foreign_function_interface>

Offers calling convention portability. Also used by CPython and OpenJDK, likely for C bindings.

## Vocabulary

### Leaf function

Function that does not call any other. Optimizations are possible for those functions, like not decrementing `rsp`: <http://stackoverflow.com/questions/13201644/why-does-the-x86-64-gcc-function-prologue-allocate-less-stack-than-the-local-var> and in x86-64 not saving function parameters passed as registers to stack.

## Dependencies

These are downloaded by:

    ./contrib/download_prerequisites

so not a part of the source tree.

- ISL: <http://isl.gforge.inria.fr/> Integer Set Library. TODO what for? Smells like optimization problems.
- GMP: <https://gmplib.org/> Multiple precision library. TODO what for?
- MPC: <http://www.multiprecision.org/index.php?prog=mpc> Complex multi precision.
- MPFR: <http://www.mpfr.org/> Multiple precision floating point Reliably.
