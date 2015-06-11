# Invocation

## Debug information

GDB can use optional debugging contained in executables to debug them.

This helps greatly, as it allows GDB to match information that is lost at compilation time with the source code, e.g.:

- what source line am I at?
- what is the name of the local variables (normally compiled just as stack offsets)

You must tell your compiler to generate debug information: it is turned off by default and not included in package managers, as it increases executable size.

For `gcc`:

    gcc -ggdb3 a.c

It is also possible to debug without debugging information, but it is much harder. In particular, you will have to rely much more on assembly level debugging, and reverse engineering the functions of variables without their name.

There are a few standards for debugging information format. DWARF is the most popular on ELF.

## Basic usage

Run executable and debug it with GDB:

    gdb a.out

Attach to a running instance of `a.out` after it was started:

    gdb -p "$pid"

the process stops at the instruction it was executing at the time.

This can also be achieved with the `attach` command.

## batch

Only run `-x` and `-ex` commands and exit.

Sample application: disassemble a single function: <http://stackoverflow.com/questions/22769246/disassemble-one-function-using-objdump>

    gdb -batch -ex 'disassemble main' -ex 'run' main.out

## ex

Run given command from string:

    gdb -ex 'break main' -ex 'run'

Must pass as single command per `-ex` argument.

## x

Run commands in the given file.

## args

You can also pass command line arguments at invocation time with:

    gdb --args executable arg0 arg1
