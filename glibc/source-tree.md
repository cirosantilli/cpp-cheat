# Source tree

Build:

    git clone git://sourceware.org/git/glibc.git
    mkdir glibc-build
    cd glibc-build
    bash ../glibc/configure --disable-sanity-checks
    make -j5

Took 4 minutes on a 2012 machine for version 2.21.

TODO every command I now run from the build directory tries to use the built libc in the current directory and segfaults. `echo $LD_LIBRARY_PATH` does not show the current directory, but doing `unset LD_LIBRARY_PATH` solves the problem. `mv libc.so.6 libc.so.6.bak` also works. TODO what to do?

## sysdeps

Contains both assembly and OS dependant optimized implementations of several functions, e.g. `sysdeps/x86_64/multiarch/memcmp-sse4.S`, `memcmp-ssse3.S`. Note the great specificity of the implementations.

Each method also has a pure C implementation when possible, e.g. `string/memcmp.c`, but that is likely to be much less efficient.

### sysdep.h

Important header file that gets included into most files of the architecture, most of which are assembly code.

Example:

- `sysdeps/x86_64/sysdep.h`

It seems that the C preprocessor is used on the assembly code, which does simply `#include <sysdep.h>`.

## multiarch

TODO?
