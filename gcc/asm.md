# asm

Great intro: http://www.ibm.com/developerworks/library/l-ia/index.html

Can be used if you really, really want to optimize at the cost of:

- architecture dependence
- tying you to GCC

If you use this, do it like the linux kernel and separate different architecture code in different dirs.

General syntax:

    asm (
        "mov $1, %%eax;"   // commands string
        : "=X" (y),   // outputs
            "=X" (z)
        : "X" (x)    // inputs
        : "%eax"     // clobbered registers
    );

where:

-   commands: actual gas code into a single c string. Remember: each command has to end in newline or `;`.

-   outputs: start with `=`. GCC has to enforce is that at the end of the `asm` block that those values are set.

-   inputs:

-   clobbered registers:

    Registers that may be modified explicitly in the assembly code.

    Normally, users have no direct access to registers, so GCC is free to optimize by leaving values in those registers for later use.

    This tells GCC not to leave values in the listed since those may be modified.

    E.g.:

        mov $0, %eax

    Clearly clobbers `eax`, so you would need to list eax in the clobber list.

    Note that certain instructions clobber registers even if they are not explicitly written in the code.

Both inputs and outputs are constraints. `X` will indicate the constraint type

## __asm__ vs asm

- <https://stackoverflow.com/questions/35131350/error-asm-undeclared-first-use-in-this-function/49830956#49830956>
- <https://stackoverflow.com/questions/3323445/what-is-the-difference-between-asm-asm-and-asm/49830990#49830990>

## Double percent

`%%`: <https://stackoverflow.com/questions/14745631/what-does-a-double-percent-sign-do-in-gcc-inline-assembly/31711138#31711138>

## volatile

TODO:

<https://gcc.gnu.org/onlinedocs/gcc-7.2.0/gcc/Extended-Asm.html> 6.45.2.1 Volatile

<http://stackoverflow.com/questions/14449141/the-difference-between-asm-asm-volatile-and-clobbering-memory>
