# gcc utility

Useful GCC command line options.

## What the gcc utility does

Nothing. Almost.

`gcc` is a driver: it orchestrates the build process, by calling other programs with the right options, notably:

- `cpp`:  preprocessor
- `cc1`: compiler. Generates `.s` file. Not in `PATH` by default.
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

## Wall

Enables many useful warnings:

    gcc -Wall

Understanding each warning and being able to write warning free code is a good way to improve language skills.

## Wextra

Enables even more useful warnings than wall.

    `gcc -Wextra`

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

`-m32` to compile IA-32 output from a 64 bit host. This does two things mainly:

- use IA-32 instructions
- link to IA-32 libraries, in particular libc. You may need to install them.

## march

Optimizes code to given CPU (arch is for architecture).

May use instructions only available to given CPU.

Optimize for current compiling machine:

    gcc -march=native

Strict 80386 instruction set. old, compatible, used on almost all desktops and laptops:

    gcc -march=i386

Arm v.7, used on mobiles today:

    gcc -march=armv7

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
- `Ofast`: optimize for speed more than `O3`, *even if it breaks standards*

Best general code optimization method:

    gcc -O3 a.c -o a.out

Always use this for production code.

## debugging

GCC has options that allow you to add debugging information to binary outputs.

This leads to larger output files, but the information can then be used by programs such as GDB or `objdump` to help debug programs, or for educational purposes.

Add debug information to executable on compilation:

    gcc -ggdb3 a.c

Options:

- `g`: generate debug info for GDB
- `ggdb`: adds more info
- `ggdb3`: adds max info. Default if 2 when ggdb is used.

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

## assembly code

If you want to interpret assembly code generated by `gcc`, the best combo is:

    gcc -fverbose-asm -S a.c

To get original line number / code from C code into `asm` comments, use either:

    gcc -c -fverbose-asm -Wa,-adhln a.c

or:

    gcc -ggdb3 -o a.o a.c
    objdump -S a.o

### -S

Generate assembly code:

    gcc -S a.c

Generates gas assembly code to a new file called `a.S`.

## -f options

TODO What are the `-f` options for in general? Give examples.

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

## -Wa options

Same as `-Xassembler`.

Example:

    gcc -c -fverbose-asm -Wa,-adhln a.c


## -Xassembler

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

## l

## Linker options

### nostdlib

Don't link to the stdlib.

### nostartfiles

TODO

### nodefaultlibs

TODO

### static

Link statically to all libraries, not just glibc.

    gcc -static main.c

The resulting build has no dependencies:

    ldd a.out

TODO Link statically only to glibc: <http://stackoverflow.com/questions/13187499/static-linking-glibc>

### static-libgcc

Link statically to `libgcc`. This is *not* `libc`, but an internal GCC library.

## Informational commands

### v

Get build information.

For version use `-version`.

Sample output:

    Using built-in specs.
    COLLECT_GCC=gcc
    COLLECT_LTO_WRAPPER=/usr/local/libexec/gcc/x86_64-unknown-linux-gnu/5.1.0/lto-wrapper
    Target: x86_64-unknown-linux-gnu
    Configured with: ../gcc/configure --enable-languages=c,c++
    Thread model: posix
    gcc version 5.1.0 (GCC)

Non obvious lines:

- `Using built-in specs.`. Means that the default specs files are being used, that is, `-specs` was not passed as an argument.
- `Configured with`: how `configure` was called before building

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
