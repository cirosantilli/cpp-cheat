# GCC

Cheat on the GNU Compile Collection (GCC) language extensions and command line utilities.

1.  [main.c](main.c): main `gcc` cheat
    1. [weak](weak/)
1.  [Introduction](introduction.md)
1.  [Compilation steps](compilation-steps.md)
1.  [Invocation](invocation.md)
    1. [Spec files](spec-files.md)
1.  [cpp](cpp.md)
1.  Internals
    1. [Makefile](makefile.md)
    1. [Source tree](source-tree.md)

## Scope

This will only cover C specifics. Generic ELF manipulation tools like `ld` (which can work across any language) are not included.

## Cross compile

Cross compiling means to compile a program for a different OS or architecture than the one the compiler is running.

GCC cannot cross compile for windows from Linux (TODO check).

This can be done with MinGW (TODO how).

## Infamous error messages

Error messages that are difficult to interpret for newbs:

- `struct has incomplete type = struct undefined`. You forgot to include some header.
