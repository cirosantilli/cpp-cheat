# Invocation

Useful GCC command line options.

Most important flags:

- `-std`
- `-o`
- `-c`
- `-Wall`
- `-pedantic` and `-pedantic-errors`
- `-L`, `-l` and `-I`
- `-O`
- `-g`

## What the gcc utility does

Nothing. Almost.

`gcc` is a driver: it orchestrates the build process, by calling other programs with the right options, notably:

- `cc1`: preprocessor + compiler. Generates `.s` file. Not in `PATH` by default. The external `cpp` may be called if `-save-temps` is used.
- `as`: assembler . Generates `.o` files.
- `collect2`: linker. Generates executable files. Not in `PATH`, but almost identical to `ld`.

Options you pass to GCC determine how it will call the other programs.

Therefore, to understand GCC you should first understand the other programs separately, and then just see exactly how exactly GCC is calling them.

The exact way in which GCC calls the other programs is determined by spec files.

GCC does not contain bin-utils: they are maintained in separate git repositories. Binutils has not knowledge about programming languages, only assembly, and can be used separately from GCC. Binutils is a dependency of GCC.

## Recommended compilation flags

Good discussion: <http://stackoverflow.com/questions/154630/recommended-gcc-warning-options-for-c>

Always use this for production output code if possible:

    gcc -std=c99 -pedantic-errors -Wall -Wextra -03 -march=native -o a a.c

This will make for portable, efficient code.

For test code, omit the `-03`, since that will make compilation faster.

## o

Output destination.

Default: `a.out`.

For stdout: `-o -`.

## Input from stdin

## x

Specify the language explicitly.

Required when input is from stdin with `-`.

Compile from stdin:

    echo 'int main(){}' | gcc -xc -

For a C header use `c-header`. Note that this generates a `-.gch` file:

    echo 'int i;' | gcc -xc-header -

## W options

Most of them are for warnings, but a few are not.

### Wall

Enables many useful warnings:

    gcc -Wall

Understanding each warning and being able to write warning free code is a good way to improve language skills.

#### Enable all warnings

- <http://stackoverflow.com/questions/5088460/flags-to-enable-thorough-and-verbose-g-warnings>
- <http://stackoverflow.com/questions/11714827/how-to-turn-on-literally-all-of-gccs-warnings>
- <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=31573>

### Wextra

Enables even more useful warnings than wall.

    `gcc -Wextra`

### Not warnings

#### Wp

Pass options to the preprocessor.

#### Wa

Pass options to the assembler, `cc1` by default TODO check

Example:

    gcc -c -fverbose-asm -Wa,-adhln a.c

#### Wl

Pass options to the linker. Multiple options can be separated by commas.

##### Xlinker

Pass options to the linker. Multiple options require multiple `-Xlinker` arguments.

## std

Specifies the language to be used.

Disables GCC extensions that conflict with ANSI C standard.

Sample usage:

    gcc -std=c90
    gcc -std=c99
    gcc -std=1x

`c11` will be the next version and is still being developed at the time of writing.

To allow GNU extensions:

    gcc -std=gnu90

This is necessary on projects that rely on the extensions, such as the Linux kernel.

## ansi

Don't use this, use `std` instead:

    gcc -ansi

Implies the most recent `-std` which gnu considers is stable manner (not necessarily the latest).

Changes with time, currently equals:

    gcc -std=c90

It is a bit confusing not to have a fixed version of the standard to comply to, so just use std instead.

## pedantic

Give warnings for code that does not comply with `c1x` standard:

    gcc -std=c1x -pedantic

This does not mean *FULL* compliance, but greatly increases compliance.

There is currently no full compliance check in `gcc`.

Give errors instead of warnings:

    gcc -std=c1x -pedantic-errors

## m

Machine options.

### m32

### m64

`-m32` to compile IA-32 output from a 64 bit host. This does two things mainly:

- use IA-32 instructions
- link to IA-32 libraries, in particular libc. You may need to install them.

### mfpmath

Chose between FPU and SSE for the floating point operations.

    gcc -mfpmath=387
    gcc -mfpmath=sse

### march

Optimizes code to given CPU (arch is for architecture).

May use instructions only available to given CPU.

Optimize for current compiling machine:

    gcc -march=native

Strict 80386 instruction set. old, compatible, used on almost all desktops and laptops:

    gcc -march=i386

Arm v.7, used on mobiles today:

    gcc -march=armv7

### mtune

TODO: finer than `-march`? E.g.: <http://www.valvers.com/open-software/raspberry-pi/step01-bare-metal-programming-in-cpt1> proposes:

    -march=armv7-a -mtune=cortex-a7

where `armv7-a` is an ISA, and `cortex-a7` an specific processor.

## Optimization

List possible optimizations for `-O`:

    gcc -Q -O --help=optimizers

The options:

- `O0`: no speed optimization. This is the default
- `O` : basic speed optimization. Same as `-O1`.
- `O2`: more than `O1`
- `O3`: more than `O2`
- `Og`: optimize for debugging
- `Os`: optimize for size
- `Ofast`: optimize for speed more than `O3`, *even if it breaks standards*. In 5.1, the only thing it does for C if adding `-ffast-math`.

Best general code optimization method:

    gcc -O3 a.c -o a.out

Always use this for production code.

### ffast-math

Drop strict IEEE to further optimize.

<http://stackoverflow.com/questions/6430448/why-doesnt-gcc-optimize-aaaaaa-to-aaaaaa>

### fexpensive-optimizations

Even more than `-O3`.

## debugging

GCC has options that allow you to add debugging information to binary outputs.

This leads to larger output files, but the information can then be used by programs such as GDB or `objdump` to help debug programs, or for educational purposes.

Add debug information to executable on compilation:

    gcc -ggdb3 a.c

Options:

- `g`: generate debug info for GDB
- `ggdb`: adds more info
- `ggdb3`: adds max info. Default if 2 when ggdb is used.

### fsanitize

Enable different types of static analysis to detect potential errors like undefined behaviour, memory leaks and illegal accesses.

Implemented by the in-source `libsanitize`.

## M

Don't compile, but generate a list of dependencies for the given source code in a format suitable for a makefile rule, and output it to stdout.

Dependencies are basically the file itself and the required headers.

For example, in `a.c`:

    #include <stdio.h>
    #include "a.h"

then:

    gcc -M a.c

Output to stdout:

    a.c : /usr/include/stdio.h \
        a.h

To make this even more suitable for a makefile, you should suppress the standard system files with `-MM`:

    gcc -MM a.c

giving:

    a.c : a.h

You can then use those on a makefile as:

    $(shell gcc -MM a.c)
        gcc a.c

### S

Generate assembly code:

    gcc -S a.c

Generates gas assembly code to a new file called `a.S`.

## syntax-only

Only check if the syntax is correct, don't compile anything.

    $ echo 'int i;' | gcc -fsyntax-only -xc -
    $ echo 'int i' | gcc -fsyntax-only -xc -
    <stdin>:1:1: error: expected ‘=’, ‘,’, ‘;’, ‘asm’ or ‘__attribute__’ at end of input

Note how the above code would not compile because there is no `main` function:

    $ echo 'int i;' | gcc -xc -
    /usr/lib/gcc/x86_64-linux-gnu/4.8/../../../x86_64-linux-gnu/crt1.o: In function `_start':
    (.text+0x20): undefined reference to `main'
    collect2: error: ld returned 1 exit status

As of GCC 4.8 fails on `c-header` files with "output filename specified twice" <http://stackoverflow.com/questions/12513665/how-can-i-use-g-to-get-assembly-code-for-a-c-header-hpp-file> The only solution seems to be to set the input type to `-xc`.

## Xassembler

Pass options directly to the `as` assembler.

Example:

    gcc -c -fverbose-asm -Xassembler -adhln a.c

## f

Flags.

These are regular options, most of which have value either true or false.

For true:

    gcc -ffoo

and false:

    gcc -fno-foo

Does not have any other meaning.

Not all `-f` flags are booleans however:

    gcc -frandom-seed=1234

### inline

Allow the compile to inline functions. Implied by `-O3`.

### freestanding

Compile in freestanding mode as defined by ANSI C.

### verbose-asm

Outputs comments on the generated assembly which say variable names are being operated on each statement:

    gcc -fverbose-asm -S a.c

Sample C input:

    i = 1;
    j = i;

Output without `-fverbose-asm`:

    movl $1, -64(%ebp)
    movl -64(%ebp), %eax
    movl %eax, -68(%ebp)

With `-fverbose-asm`:

    movl $1, -64(%ebp)   # ,i
    movl -64(%ebp), %eax #i, tmp123
    movl %eax, -68(%ebp) #tmp123, j

To get original line number / code from C code into `asm` comments, use either:

    gcc -c -fverbose-asm -Wa,-adhln a.c

or:

    gcc -ggdb3 -o a.o a.c
    objdump -S a.o

### profile-generate

### Profile guided optimization

<https://en.wikipedia.org/wiki/Profile-guided_optimization>

<http://stackoverflow.com/questions/4365980/how-to-use-profile-guided-optimizations-in-g>

## Preprocessor options

### I

Add directory to the include search path:

    gcc -I/some/dir main.c

### CPATH

### C_INCLUDE_PATH

Add to the search path after `-I`:

- `CPATH`: all languages
- `C_INCLUDE_PATH`: only C
- `CPLUS_INCLUDE_PATH`: only C++

Trailing or leading `:` implies current directory:

    :/some/dir
    /some/dir:
    /some/dir::/another/dir

### nostdinc

Don't use the standard include path.

Allows you to set up a custom path with:

    gcc -nostdinc -I/my/custom/path/

<http://stackoverflow.com/questions/2988779/gcc-how-to-ignore-standard-include-paths>

## l

## Linker options

### nostdlib

Don't link to the stdlib.

### nostartfiles

Don't pass `crt1.o`, `crti.o`, and other `crt` files to the linker, as normally done by default.

If you use this, you must provide your own, or else the linker will not find the `_start` symbol which is present in those files.

### nodefaultlibs

TODO: vs `nostdlib`?

### static

Link statically to all libraries, not just glibc.

    gcc -static main.c

The resulting build has no dependencies:

    ldd a.out

The effect is that after `-lxyz`, only `libxyz.a` is searched in the search path, not `libxyz.so`.

Without `-static` TODO: `-lxyz` seems to use `libxyz.a`, but that may lead to link errors.

TODO links some libraries statically and others dynamically:

- <http://stackoverflow.com/questions/13187499/static-linking-glibc>
- <http://stackoverflow.com/questions/809794/use-both-static-and-dynamically-linked-libraries-in-gcc>
- <http://stackoverflow.com/questions/6578484/telling-gcc-directly-to-link-a-library-statically>

### static-libgcc

Link statically to `libgcc`. This is *not* `libc`, but an internal GCC library.

## Informational commands

### verbose

Get basic GCC version information:

    gcc --version

Sample output:

    gcc (Ubuntu 4.8.2-19ubuntu1) 4.8.2
    Copyright (C) 2013 Free Software Foundation, Inc.
    This is free software; see the source for copying conditions.  There is NO
    warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

This is only a general indication of version, since there are many configuration options. To see that, use `-v`.

### v

Get verbose build information.

For shorter version information use `--version`.

Sample output:

    Using built-in specs.
    COLLECT_GCC=gcc
    COLLECT_LTO_WRAPPER=/usr/local/libexec/gcc/x86_64-unknown-linux-gnu/5.1.0/lto-wrapper
    Target: x86_64-unknown-linux-gnu
    Configured with: ../gcc/configure --enable-languages=c,c++
    Thread model: posix
    gcc version 5.1.0 (GCC)

Non-obvious lines:

- `Using built-in specs.`. Means that the default specs files are being used, that is, `-specs` was not passed as an argument.
- `Configured with`: how `configure` was called before building

If you also compile a program, you will see many more lines explaining how exactly gcc called its subprograms:

    Using built-in specs.
    COLLECT_GCC=gcc
    COLLECT_LTO_WRAPPER=/usr/lib/gcc/x86_64-linux-gnu/4.8/lto-wrapper
    Target: x86_64-linux-gnu
    Configured with: ../src/configure -v --with-pkgversion='Ubuntu 4.8.2-19ubuntu1' --with-bugurl=file:///usr/share/doc/gcc-4.8/README.Bugs --enable-languages=c,c++,java,go,d,fortran,objc,obj-c++ --prefix=/usr --program-suffix=-4.8 --enable-shared --enable-linker-build-id --libexecdir=/usr/lib --without-included-gettext --enable-threads=posix --with-gxx-include-dir=/usr/include/c++/4.8 --libdir=/usr/lib --enable-nls --with-sysroot=/ --enable-clocale=gnu --enable-libstdcxx-debug --enable-libstdcxx-time=yes --enable-gnu-unique-object --disable-libmudflap --enable-plugin --with-system-zlib --disable-browser-plugin --enable-java-awt=gtk --enable-gtk-cairo --with-java-home=/usr/lib/jvm/java-1.5.0-gcj-4.8-amd64/jre --enable-java-home --with-jvm-root-dir=/usr/lib/jvm/java-1.5.0-gcj-4.8-amd64 --with-jvm-jar-dir=/usr/lib/jvm-exports/java-1.5.0-gcj-4.8-amd64 --with-arch-directory=amd64 --with-ecj-jar=/usr/share/java/eclipse-ecj.jar --enable-objc-gc --enable-multiarch --disable-werror --with-arch-32=i686 --with-abi=m64 --with-multilib-list=m32,m64,mx32 --with-tune=generic --enable-checking=release --build=x86_64-linux-gnu --host=x86_64-linux-gnu --target=x86_64-linux-gnu
    Thread model: posix
    gcc version 4.8.2 (Ubuntu 4.8.2-19ubuntu1)
    COLLECT_GCC_OPTIONS='-v' '-mtune=generic' '-march=x86-64'
     /usr/lib/gcc/x86_64-linux-gnu/4.8/cc1 -quiet -v -imultiarch x86_64-linux-gnu main.c -quiet -dumpbase main.c -mtune=generic -march=x86-64 -auxbase main -version -fstack-protector -Wformat -Wformat-security -o /tmp/ccsZiMpp.s
    GNU C (Ubuntu 4.8.2-19ubuntu1) version 4.8.2 (x86_64-linux-gnu)
        compiled by GNU C version 4.8.2, GMP version 5.1.3, MPFR version 3.1.2-p3, MPC version 1.0.1
    GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
    ignoring nonexistent directory "/usr/local/include/x86_64-linux-gnu"
    ignoring nonexistent directory "/usr/lib/gcc/x86_64-linux-gnu/4.8/../../../../x86_64-linux-gnu/include"
    #include "..." search starts here:
    #include <...> search starts here:
     /usr/lib/gcc/x86_64-linux-gnu/4.8/include
     /usr/local/include
     /usr/lib/gcc/x86_64-linux-gnu/4.8/include-fixed
     /usr/include/x86_64-linux-gnu
     /usr/include
    End of search list.
    GNU C (Ubuntu 4.8.2-19ubuntu1) version 4.8.2 (x86_64-linux-gnu)
        compiled by GNU C version 4.8.2, GMP version 5.1.3, MPFR version 3.1.2-p3, MPC version 1.0.1
    GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
    Compiler executable checksum: dc75e0628c9356affcec059d0c81cc01
    COLLECT_GCC_OPTIONS='-v' '-mtune=generic' '-march=x86-64'
     as -v --64 -o /tmp/ccaVhizy.o /tmp/ccsZiMpp.s
    GNU assembler version 2.25 (x86_64-unknown-linux-gnu) using BFD version (GNU Binutils) 2.25
    COMPILER_PATH=/usr/lib/gcc/x86_64-linux-gnu/4.8/:/usr/lib/gcc/x86_64-linux-gnu/4.8/:/usr/lib/gcc/x86_64-linux-gnu/:/usr/lib/gcc/x86_64-linux-gnu/4.8/:/usr/lib/gcc/x86_64-linux-gnu/
    LIBRARY_PATH=/usr/lib/gcc/x86_64-linux-gnu/4.8/:/usr/lib/gcc/x86_64-linux-gnu/4.8/../../../x86_64-linux-gnu/:/usr/lib/gcc/x86_64-linux-gnu/4.8/../../../../lib/:/lib/x86_64-linux-gnu/:/lib/../lib/:/usr/lib/x86_64-linux-gnu/:/usr/lib/../lib/:/usr/lib/gcc/x86_64-linux-gnu/4.8/../../../:/lib/:/usr/lib/
    COLLECT_GCC_OPTIONS='-v' '-mtune=generic' '-march=x86-64'
     /usr/lib/gcc/x86_64-linux-gnu/4.8/collect2 --sysroot=/ --build-id --eh-frame-hdr -m elf_x86_64 --hash-style=gnu --as-needed -dynamic-linker /lib64/ld-linux-x86-64.so.2 -z relro /usr/lib/gcc/x86_64-linux-gnu/4.8/../../../x86_64-linux-gnu/crt1.o /usr/lib/gcc/x86_64-linux-gnu/4.8/../../../x86_64-linux-gnu/crti.o /usr/lib/gcc/x86_64-linux-gnu/4.8/crtbegin.o -L/usr/lib/gcc/x86_64-linux-gnu/4.8 -L/usr/lib/gcc/x86_64-linux-gnu/4.8/../../../x86_64-linux-gnu -L/usr/lib/gcc/x86_64-linux-gnu/4.8/../../../../lib -L/lib/x86_64-linux-gnu -L/lib/../lib -L/usr/lib/x86_64-linux-gnu -L/usr/lib/../lib -L/usr/lib/gcc/x86_64-linux-gnu/4.8/../../.. /tmp/ccaVhizy.o -lgcc --as-needed -lgcc_s --no-as-needed -lc -lgcc --as-needed -lgcc_s --no-as-needed /usr/lib/gcc/x86_64-linux-gnu/4.8/crtend.o /usr/lib/gcc/x86_64-linux-gnu/4.8/../../../x86_64-linux-gnu/crtn.o

### print-search-dirs

    gcc -print-search-dirs | tr ':' '\n'

Sample output:

    install
     /usr/local/lib/gcc/x86_64-unknown-linux-gnu/5.1.0/
    programs
     =/usr/local/libexec/gcc/x86_64-unknown-linux-gnu/5.1.0/
    /usr/local/libexec/gcc/x86_64-unknown-linux-gnu/5.1.0/
    /usr/local/libexec/gcc/x86_64-unknown-linux-gnu/
    [...]
    libraries
     =/usr/local/lib/gcc/x86_64-unknown-linux-gnu/5.1.0/
    /usr/local/lib/gcc/x86_64-unknown-linux-gnu/5.1.0/../../../../x86_64-unknown-linux-gnu/lib/x86_64-unknown-linux-gnu/5.1.0/
    /usr/local/lib/gcc/x86_64-unknown-linux-gnu/5.1.0/../../../../x86_64-unknown-linux-gnu/lib/x86_64-linux-gnu/
    [...]

The search paths are:

- `install` TODO
- `programs`: where GCC will look for its internal programs like `cc1` and `collect2`. GCC also uses the `PATH` for external programs, which are called even though they are not there.

### print-file-name

Find in the `libraries` section of `-print-search-dirs`.

This horribly named option searches in the library path for a given library:

    gcc -print-file-name=libc.so

If the library is found it returns the full path:

    /usr/lib/x86_64-linux-gnu/libc.so

otherwise, it returns the input string:

    libc.so

which indicates that the program only checks if directories exist, not the actual file searched for.

### print-prog-name

Same as `-print-file-name`, but for the internal called programs instead.
