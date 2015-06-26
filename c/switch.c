/*
# switch

# case

    6.8.4.2 The switch statement
*/

#include "common.h"

int main() {

    /* Basic example. */
    {
        int i = 0;
        int j;
        switch(i) {
            case 0:
                j = 0;
            break;
            case 1:
                j = 1;
            break;
            case 2:
                j = 2;
            break;
            default:
                j = 3;
            break;
        }
    }

    /*
    # vs if else

        - http://stackoverflow.com/questions/97987/advantage-of-switch-over-if-else-statement
        - http://stackoverflow.com/questions/6805026/is-switch-faster-than-if

        Why does this exists (could be done with if):

        - easier to for the compiler to notice that it can optimize
            as binary search or indirect jumps https://en.wikipedia.org/wiki/Indirect_branch
        - do not repeat the deciding variable / expression many times
        - readability

        So use switch whenever possible.
    */
    {
        /* Exact same functionality as the example above. */
        int i = 0;
        int j;
        if (i == 0) {
            j = 0;
        } else if (i == 1) {
            j = 1;
        } else if (i == 2) {
            j = 2;
        } else {
            j = 3;
        }
    }

    /*
    Decision variable must be integral type.

    Otherwise it would not be possible to implement with the jump table,
    and it would be useless.
    */
    {
        float i = 0.0;
        /*
        switch(i) {
            case 0.0:
            break;
            case 1.0:
            break;
        }
        */
    }

    /*
    `case` expressions must be constant expressions.

    Otherwise, cannot be implemented with the jump table and thus useless.
    */
    {
        int i = 1;
        switch(i) {
            case 0 * 0:
            break;
            case 0 + 1:
            break;
            /* ERROR. */
            /*case time(NULL):*/
            break;
        }
    }

    {
        int i, j;
        for(i = -1; i < 6; i++) {
            switch (i) {
                case 0:

                    assert(i == 0);

                    /* OK new inner scope */
                    int j;

                    /* ERROR redeclaration */
                    /*int i = 1;*/

                break;

                case 1:

                    assert(i == 1);

                    /* ERROR single inner scope. */
                    /*int j;*/

                break;

                /* Same action for multiple cases. */
                case 2:
                case 3:

                    assert(i == 2 || i == 3);

                break;

                /* Google C++ style recommends the following style. */
                case 4: {
                    assert(i == 4);
                    break;
                }
                case 5: {
                    assert(i == 5);
                    break;
                }

                default:
                    assert(i != 0 && i != 1);
                break;
            }
        }
    }

    /*
    -   case statements are just like GOTO labels

    -   break is like a jump

    -   each case does not need a corresponding break

    -   and switch statements can contain any other construct like `if` or `while`
        even outside of a case break pair.

    The major application of this is to impress your friends
    with your mastery of C obscurantism.

    However there is a classic optimization trick that relies on that:
    http://en.wikipedia.org/wiki/Duff%27s_device

    # Duff's device
    */
    {
        int i = 0;
        switch (2) {
            while (i < 2) {
            label_switch_in_while:
            case 0:
                i++;
            }
            case 1:
                i++;
                break;
            case 2:
                goto label_switch_in_while;
        }
        printf("%d\n", i);
        assert(i == 3);
    }

    return EXIT_SUCCESS;
}
