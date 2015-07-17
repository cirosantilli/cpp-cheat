# Internals

Hardware vs software breakpoints: <http://stackoverflow.com/questions/8878716/what-is-the-difference-between-hardware-and-software-breakpoints> x86 has 4 registers which can raise an exception is the PC points to the instruction stored in them. GDB can then deal with the exception and take over.

## Communication

- bugs and feature requests at: <https://sourceware.org/bugzilla>
- patches: <https://sourceware.org/ml/gdb-patches/>

## Vocabulary

- `sal`: symtable and line. Both are often passed around together. TODO why.

## Source tree

- `cli/cli-cmds.c`: defines the built-in commands. Good place to start probing. Not *all* commands are there however. Grep for strings, e.g. `"break"`.
