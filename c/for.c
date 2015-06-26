/*
# for

# for vs while

    In theory, whatever you can to with for you can do with while.

    However x86 has a loop instruction that increments and
    contional jumps in a single step.

    Therefore, using a simple for is a better hinto to your
    compiler to use this more efficient looping instruction.

    Moral: if you when know how many loops you will do, use `for`,
    otherwise use `while`.

    Using for also serves as self documentation telling readers that you know
    beforehand how many times the loop will execute.
*/

#include "common.h"

int main() {
    /* Basic example. */
    {
        int i;
        int is[] = { 0, 1, 2 };
        for (i = 0; i < 3; ++i) {
            assert(i == is[i]);

            /* OK new scope. */
            int i = -1;
            /* From now on, the loop's `i` is invisble. */
            assert(i == -1);
        }
        assert(i == 3);
    }

    /*
    Like for `if`, if there is only a single statement,
    braces can be omitted.
    */
    {
        int i;
        int is[] = { 0, 1, 2 };
        for (i = 0; i < 3; ++i)
            assert(i == is[i]);
            /* ERROR redeclaration note different if bracketes used. */
            /*int i;*/
    }

    /*
    Multiple loop variables: one of the few "uses" of the comma operator.

    Arguably though, `while` loops are more readable in that case,
    like in any other case that is not a straight single integer variable increase.

    TODO check. Is this really the comma operator?
    */
    {
        int i;
        float f;
        for (i = 0, f = 0.0f; i * f < 7; i++, f += 0.5) {}
        assert(i == 4);
    }

#if __STDC_VERSION__ >= 199901L
    {
        /* Putting `int i = 0` inside the `for` is only possible in C99. */
        {
            int is[] = {0, 1, 2};
            for (int i = 0; i < 3; ++i) {
                assert(i == is[i]);
                /* ERROR: redeclaration. */
                /*int i;*/
            }
            /* ERROR undeclared. */
            /*assert(i == 3);*/
        }

        /*
        This allows for a second way of initializing multiple variables
        in a single for, besides the existing comma operator.

        This syntax does not however allow to initialize
        two variables of different types.
        */
        {
            int is[] = {0, 1, 2};
            for (int i = 0, j = 0; j < 30; ++i, j += 10) {
                assert(i == is[i]);

                /* ERROR: redeclaration. */
                /*int i;*/
            }
        }
    }
#endif

    /* Nested loops. */
    {
        /* Basic example. */
        {
            int n = 0;
            int is[] = {0, 0, 1, 1};
            int js[] = {0, 1, 0, 1};
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 2; j++) {
                    assert(i == is[n]);
                    assert(j == js[n]);
                    n++;
                }
            }
        }

        /*
        # Break out of nested loops

            http://stackoverflow.com/questions/1257744/can-i-use-break-to-exit-multiple-nested-for-loops

            One of the few widely accepted uses of goto.

            Languages like Java have labeled loops to avoid the goto.

        */
        {
            /* TODO example: find number in a two dimensional array. */
        }
    }

    /* Different loop step. */
    {
        int n = 5;
        int step = 2;
        int is[] = {0, 1, 2, 3, 4};
        int js[] = {0, 2, 4};
        int js2[] = {1, 3};
        int j = 0;
        for (int i = 0; i < n; i += step) {
            assert(js[j] == is[i]);
            if (i < n - step + 1)
                assert(js2[j] == is[i + 1]);
            j++;
        }
    }

    /* # Backward loops. */
    {
        int n = 3;
        int is[] = { 0, 1, 2 };
        int js[] = { 2, 1, 0 };
        int j = 0;
        for (int i = n - 1; i >= 0; --i) {
            assert(is[i] == js[j]);
            j++;
        }

        /*
        # Backward loops with unsined loop variables

            Here things get messy: <http://stackoverflow.com/questions/665745/whats-the-best-way-to-do-a-reverse-for-loop-with-an-unsigned-index>

            It becomes clear why the google c++ style recommends not to use unsigned,
            but how can that be avoided for example for `size_t`?
        */
        {
            /* Infinite loop, since `i >= 0` always holds! */
            /*
            {
                int n = 3;
                int is[] = { 0, 1, 2 };
                int js[] = { 2, 1, 0 };
                int j = 0;
                for (unsigned int i = n - 1; i >= 0; --i) {
                    assert(is[i] == js[j]);
                    j++;
                }
            }
            */

            /*
            Two variables solution.

            Downside: one more variable, one extra operation per loop. 

            Upside: very clear.
            */
            {
                unsigned int n = 3;
                int is[] = { 0, 1, 2 };
                for (unsigned int i_fake = n; i_fake > 0; --i_fake) {
                    unsigned int i = i_fake - 1;
                    assert(is[i] == i);
                }
            }

            /*
            Module madness solution.

            Downside: mind twisting.

            Upside: efficient: no extra var or operation.
            */
            {
                unsigned int n = 3;
                int is[] = { 0, 1, 2 };
                for (unsigned int i = n - 1; i < n; --i) {
                    assert(i == is[i]);
                }
            }

            /*
            Post increment solution.

            Mnemonic: the goes to operator `-->`

            Downside: only works for step of 1.

            Upside: efficient: no extra var or operation.
            */
            {
                unsigned int n = 3;
                int is[] = { 0, 1, 2 };
                for (unsigned int i = n - 1; i-- > 0;) {
                    assert(i == is[i]);
                }
            }
        }
    }

    return EXIT_SUCCESS;
}
