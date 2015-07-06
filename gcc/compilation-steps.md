# Compilation steps

To observe exactly what is one on each step, use:

    gcc -v main.c

The exact steps are determined by the spec file, <https://gcc.gnu.org/onlinedocs/gcc-4.8.1/gcc/Spec-Files.html> You can view the default with:

    gcc -dumpspecs

You can add your own specs after the default with:

    gcc -specs=file

Generate all external intermediate steps (`.i`, `.s`, `.o`) in the current directory:

    gcc -save-temps a.c

`gcc` is a high level wrapper to multiple compilation steps which are done by different programs.

Only expanded macros with the C preprocessor:

    cpp a.c > a.i
    cpp b.c > b.i

Different languages have different preprocessors

Generate human readable assembly code:

    gcc -S a.i -o a.s
    gcc -S b.i -o b.s

Specify format:

    gcc -masm=att -S a.c -o a.s
    gcc -masm=intel -S a.c -o a.s

Default format: AT&T which is historically what has larger GCC support.

Make machine code from assembly code:

    as -o a.o a.s
    as -o b.o b.s

This transforms human readable formats into binary object files

Make machine code from C directly:

    gcc -c a.c -o a.o
    gcc -c b.c -o b.o

Link object files into single executable:

    ld -o ab.out a.o b.o

Expects `main` to be defined (actual ELF entry point is `_start`) TODO this does not link to the stdlib. How to make it?

All above steps in one:

    gcc a.c b.c -o ab.out

If you use make, it is faster to generate `.o` and keep them, since if the source does not change, make will not recompile the corresponding `.o`
