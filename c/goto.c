/*
# goto

    One of the most basic loops: tranlates to an unconditional `jmp` in x86.
*/

#include "common.h"

int goto_func(int i) {
    /*goto goto_func_after;*/
    in_func_label:
    return 1;
}

int main() {
    /*
    However, avoid using this as it may generate unreadable code.

    Opinions vary, but possible acceptable uses are:

    -   break out of nested loops, widely supported

    -   any forward jump, e.g. for error handling.
        Those are equivalent to return, which is well accepted.

    Very few people support gotos that go backwards.

    `return` is essentially a forward jump inside a function.
    */

    /* Basic example. */
    {
        goto basic_example;
            assert(0);
        basic_example:
            assert(1);
    }

    /*
    goto cannot cross functions: that would lead to crazy
    things like uninitialized parameters, and no return.

    Use `setjmp` for that.
    */
    {
        int i;
        goto_func_after:
            i = 1;
        /*goto in_func_label;*/
    }

    /* Labels cannot be at the end of compound statments */
    {
        { /*label_end_compound:*/ }
        { label_end_compound: 1; }
    }

    /* Labels and loops */
    {
        int i;
        for ( /*label_in_for:*/ i = 0; i < 2; i++)
        label_after_if:
        {
            label_after_if2: 1;
        }
    }

    /* Labels and switch. */
    {
        int a = 1;
        switch (a) {
            case 0:
            label_case_0:
                assert(a == 1);
            break;
            case 1:
                goto label_case_0;
            break;
        }
    }

    /*
    Store label in variable and jump to it:

    - http://stackoverflow.com/questions/1777990/c-programming-address-of-a-label
    - http://stackoverflow.com/questions/938518/how-to-store-goto-labels-in-an-array-and-then-jump-to-them

    Impossible.
    */

    return EXIT_SUCCESS;
}
