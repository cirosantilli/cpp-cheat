/*
# Assembly

# Inline assembly

# asm

    Great intro: http://www.ibm.com/developerworks/library/l-ia/index.html

    Can be used if you really, really want to optimize at the cost of:

    - architecture dependance
    - tying you to gcc

    If you use this, do it like the linux kernel and separate different architecture
    code in different dirs.

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

    -   outputs: start with `=`. gcc has to enforce is that at the end of the `asm` block that those values are set.

    -   inputs:

    -   clobbered registers:

        Registers that may be modified explicitly in the assembly code.

        Normally, users have no direct access to registers,
        so gcc is free to optimize by leaving values in those registers for later use.

        This tells gcc not to leave values in the listed since those may be modified.

        E.g.:

            mov $0, %eax

        Clearly clobbers eax, so you would need to list eax in the clobber list.

        Note that certain instructions clobber registers
        even if they are not explicitly written in the code.

    Both inputs and outputs are constraints. `X` will indicate the constraint type

    TODO: # __asm__ vs asm
    TODO: # asmlinkage
    TODO: # asm volatile
*/

#include "common.h"

int main(void) {
#if defined(__i386__) || defined(__x86_64__)
    puts("__i386__ || __x86_64__");

    /*
    # Basic asm

    # No colon

        There are two types of asm: basic and extended.

        The basic one does not have a colon after the string.

        Basic is strictly less powerful: it can only deal with literal commands.
    */
    {
#ifdef __i386__
        asm volatile ("push %eax; mov $1, %eax; pop %eax;");
#else
        asm volatile ("push %rax; mov $1, %rax; pop %rax;");
#endif
    }

    /*
    # m constraint

        Instructs GCC to keep value of given expressions into RAM.

        This is the most basic way to get/set values of C variables in assembly code.
    */
    {
        int in = 1;
        int out = 0;
        /*out = in*/
        asm volatile (
            "movl %1, %%eax;"
            "movl %%eax, %0"
            : "=m" (out)
            : "m" (in)
            : "%eax"
        );
        assert(out == 1);
    }

    /* No input. */
    {
        int out = 0;
        /*out = 1*/
        asm volatile (
            "movl $1, %0"
            : "=m" (out)
        );
        assert(out == 1);
    }

    /* Simple example using floats */
    {
        float in = 1.0;
        float out = 0.0;
        /*out = -in*/
        asm volatile (
            "flds %1;"
            "fchs;"
            "fstps %0;"
            : "=m" (out)
            : "m" (in)
        );
        assert(out == -1.0);
    }

    /* Input and output can be the same memory location. */
    {
        float x = 1.0;
        /*x = -x*/
        asm (
            "flds %1;"
            "fchs;"
            "fstps %0;"
            : "=m" (x)
            : "m" (x)
        );
        assert(x == -1.0);
    }

    /*
    # Register constraints

        https://gcc.gnu.org/onlinedocs/gcc/Simple-Constraints.html

        Tell GCC to automatically read memory into registers or write registers into memory

        This is more precise and complicated than using `m`:

        - r: gcc chooses any free register
        - a: %eax
        - b: %ebx
        - c: %ecx
        - d: %edx
        - S: %esi
        - D: %edi
        - 0: matching register
    */

    /*
    # r register constraint

        gcc will automatically put the value of `in` from RAM into a register for us
        and `out` from a register into ram at the end

        We can do an `inc` operation directly on both `%1` and `%0`,
        so they must both already be inside a registers as expected

        GCC just makes sure they are written from/to memory before/after the operations.
    */
    {
        int in = 0;
        int out = 0;
        /*out = in + 2*/
        asm (
            "incl %1;"
            "movl %1, %0;"
            "incl %0;"
            : "=r" (out)
            : "r" (in)
        );
        /* in was not modified by inc. It had already been moved to a register. */
        assert(in == 0);
        /* Out was modified. But only after our custom assembly executed. */
        assert(out == 2);
    }

    /*
    # Matching constraint

    # 0 constraint

        Represented by digits.

        Specifies that an input/output has the same constraint as another one.

        Often used when we want a single variable to be both input and output
        and minimize the use of new registers.
    */
    {
        int x = 0;
        asm (
            "incl %0"
            : "=r" (x)
            : "0" (x) /* x has the same constraint
                            as constraint 0 (`r`)*/
        );
        assert(x == 1);
    }

    /*
    # Specific register constraints

    # a

        Forces it to be put into eax.
    */
    {
        int x = 0;
        asm (
            "incl %%eax"
            : "=a" (x)
            : "0" (x)
        );
        assert(x == 1);
    }

    /*
    # Register variables

        http://stackoverflow.com/questions/2114163/reading-a-register-value-into-a-c-variable

        https://gcc.gnu.org/onlinedocs/gcc-4.4.2/gcc/Explicit-Reg-Vars.html
    */
    {
        register int eax asm ("eax");
        asm ("mov $1, %%eax;" : : : "%eax");
        assert(eax == 1);
        asm ("mov $2, %%eax;" : : : "%eax");
        assert(eax == 2);
    }

    /*
    # modifiers

        https://gcc.gnu.org/onlinedocs/gcc-4.7.0/gcc/Modifiers.html#Modifiers

    # =

        Says that a value may have been modified by asm.

        TODO: `=` vs indicating that it is an output? (before the second `:`?

    # +

        Both read from and written to.
    */

    /*
    # asm volatile

        http://stackoverflow.com/questions/14449141/the-difference-between-asm-asm-volatile-and-clobbering-memory

        TODO minimal example.
    */

    /*
    # volatile variable modified in asm

        TODO do you need to mark variables modified in `asm` as volatile?

        I think this is exactly what the `=` modifier does already, so maybe not.
    */
#endif
    return EXIT_SUCCESS;
}
