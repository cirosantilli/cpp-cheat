#include "common.h"

int main(void) {
#if defined(__i386__) || defined(__x86_64__)
    puts("__i386__ || __x86_64__");

    /* # Basic asm vs extended asm
     *
     * There are two types of asm: basic and extended.
     *
     * The basic one does not have a colon after the string.
     *
     * Basic is strictly less powerful: it can only deal with literal commands,
     * so you basically (badum tish) never want to use it.
     *
     * All other examples in this section are extended asm.
     *
     * https://gcc.gnu.org/onlinedocs/gcc-7.2.0/gcc/Extended-Asm.html
     */
    {
#ifdef __i386__
        __asm__ ("push %eax; mov $1, %eax; pop %eax;");
#else
        __asm__ ("push %rax; mov $1, %rax; pop %rax;");
#endif
    }

    /* # m constraint
     *
     * Memory.
     *
     * Instructs GCC to keep value of given expressions into RAM.
     *
     * This is the most basic way to get/set values of C variables in assembly code.
     */
    {
        /* OK */
        {
            uint32_t in = 1;
            uint32_t out = 0;
            __asm__ (
                "movl %1, %%eax;"
                "inc %%eax;"
                "movl %%eax, %0"
                : "=m" (out) /* Outputs. '=' means written to. */
                : "m" (in)   /* Inputs. No '='. */
                : "%eax"     /* Clobbers: tell GCC that eax has been is modified. */
            );
            assert(out == in + 1);
        }

#if 0
        /* ERROR: memory input 1 is not directly addressable */
        {
            uint32_t out = 0;
            __asm__ (
                "movl %1, %%eax;"
                "inc %%eax;"
                "movl %%eax, %0"
                : "=m" (out)
                : "m" (1)
                : "%eax"
            );
            assert(out == 1 + 1);
        }
#endif
    }

    /* Multiple inputs. */
    {
        uint32_t in0 = 1;
        uint32_t in1 = 2;
        uint32_t out = 0;
        __asm__ (
            "movl %1, %%eax;"
            "movl %2, %%ebx;"
            "addl %%ebx, %%eax;"
            "movl %%eax, %0"
            : "=m" (out)
            : "m" (in0),
              "m" (in1)
            : "%eax"
        );
        assert(out == in0 + in1);
    }

    /* The input memory can be the same as the output memory.
     *
     * io++
     *
     * We must mark it as `+` which means that the memory is used for both read and write.
     */
    {
        uint32_t io = 0;
        __asm__ (
            "movl %0, %%eax;"
            "inc %%eax;"
            "movl %%eax, %0;"
            : "+m" (io) /* + means both read and written to. */
            :           /* No input. */
            : "%eax"
        );
        assert(io == 1);
    }

    /* Float example. */
    {
        float in = 1.0;
        float out = 0.0;
        /* out = -in */
        __asm__ (
            "flds %1;"
            "fchs;"
            "fstps %0;"
            : "=m" (out)
            : "m" (in)
        );
        assert(out == -1.0);
    }

    /* # Register constraints
     *
     * https://gcc.gnu.org/onlinedocs/gcc/Simple-Constraints.html
     *
     * Tell GCC to automatically read memory into registers or write registers into memory
     *
     * This is more precise and complicated than using `m`:
     *
     * - r: gcc chooses any free register
     * - a: %eax
     * - b: %ebx
     * - c: %ecx
     * - d: %edx
     * - S: %esi
     * - D: %edi
     * - 0: matching register
     */

    /* # r register constraint
     *
     * GCC will automatically put the value of `in` from RAM into a register for us
     * and `out` from a register into ram at the end
     *
     * GCC just makes sure they are written from/to memory before/after the operations.
     *
     * This is great, as it:
     *
     * - makes our assembly shorter: no memory moves nor clobbers are needed
     * - allows GCC to optimize further
     */
    {
        const uint32_t in0 = 0;
        uint32_t in = in0;
        uint32_t out = 0;
        __asm__ (
            "incl %1;"
            "movl %1, %0;"
            "incl %0;"
            : "=r" (out)
            : "r"  (in)
        );
        assert(in == in0);
        assert(out == in0 + 2);
    }

    /* # 0 matching constraint
     *
     * Specifies that an input maps to the same as a given output.
     *
     * https://stackoverflow.com/questions/48381184/can-i-modify-input-operands-in-gcc-inline-assembly/48381252#48381252
     *
     * - vs '+': allows biding two different variables
     * - vs 'a': allows referring to an 'r', which is automatically allocated by GCC
     */
    {
        const uint32_t in0 = 1;
        uint32_t in = in0;
        uint32_t out = 0;
        __asm__ (
            "incl %0"
            : "=r" (out)
            : "0" (in)
        );
        assert(in == in0);
        assert(out == in0 + 1);
    }

    /* # a register constraint
     *
     * Forces it to be put into eax.
     *
     * Clobber done automatically for us.
     *
     * Just use 'r' whenever you can.
     */
    {
        uint32_t x = 0;
        __asm__ (
            "incl %%eax"
            : "=a" (x)
            : "a"  (x)
        );
        assert(x == 1);
    }

    /* # Register variables
     *
     * http://stackoverflow.com/questions/2114163/reading-a-register-value-into-a-c-variable
     *
     * https://gcc.gnu.org/onlinedocs/gcc-4.4.2/gcc/Explicit-Reg-Vars.html
     */
    {
        register uint32_t eax __asm__ ("eax");
        __asm__ ("mov $1, %%eax;" : : : "%eax");
        assert(eax == 1);
        __asm__ ("mov $2, %%eax;" : : : "%eax");
        assert(eax == 2);
    }
#endif
    return EXIT_SUCCESS;
}
