# GCC

Cheat on the GNU Compile Collection (GCC) language extensions and command line utilities.

1.  [Introduction](introduction.md)
    1. [Compilation steps](compilation-steps.md)
    1. [Invocation](invocation.md)
    1. [Spec files](spec-files.md)
    1. [GCC as library](gcc-as-library.md)
1.  Extensions
    1.  Types
        1. [Empty struct](empty_struct.c)
        1. [Zero length array](zero_length_array.c)
        1. [128-bit int](128_bit_int.c)
        1. [Complex integer](complex_integer.c)
        1. [__auto_type](auto_type.c)
    1.  Language
        1.  [Literals](literals.c)
        1.  [Identifiers](identifiers.c)
        1.  [Nested functions](nested_functions.c)
        1.  [typeof](typeof.c)
        1.  [Case range](case_range.c)
        1.  [Array range initializer](array_range_initializer.c)
        1.  [Local label](local_label.c)
        1.  [Statment expression](statment_expression.c)
    1.  [Attribute](attribute.c)
        1.  Variable
            1.  [weak](weak/)
            1.  [Vector extensions](vector.c)
        1.  Function
            1.  [sentinel](sentinel.c)
    1.  [asm](asm.c)
    1.  [Built-in functions]()
        1. [alloca()](alloca.c)
        1. [__atomic_fetch_add](atomic_fetch_add.c)
        1. [__builtin_expect](builtin_expect.c)
        1. [__builtin_constant_p](builtin_constant_p.c)
        1. [__builtin_prefetch](builtin_prefetch.c)
        1. [__builtin_return_address](builtin_return_address.c)
1.  cpp
    1. [cpp invocation](cpp-invocation.md)
    1. [cpp](cpp.c)
1.  Internals
    1.  [Build](build.md)
        1. [Cross compiler](cross-compiler.md)
    1.  [Compilation passes](compilation-passes.md)
    1.  [Source tree](source-tree.md)
    1.  [libgcc](libgcc.md)

WIP

1. [IDE](ide.md)
1. [Spec files](spec-files.md)

## Scope

This will only cover C specifics. Generic ELF manipulation tools like `ld` (which can work across any language) are not included.

## Cross compile

Cross compiling means to compile a program for a different OS or architecture than the one the compiler is running.

GCC cannot cross compile for windows from Linux (TODO check).

This can be done with MinGW (TODO how).

## Infamous error messages

Error messages that are difficult to interpret for newbs:

- `struct has incomplete type = struct undefined`. You forgot to include some header.
