# Internals

Hardware vs software breakpoints: <http://stackoverflow.com/questions/8878716/what-is-the-difference-between-hardware-and-software-breakpoints> x86 has 4 registers which can raise an exception is the PC points to the instruction stored in them. GDB can then deal with the exception and take over.

## Vocabulary

- `sal`: symtable and line. Both are often passed around together. TODO why.
