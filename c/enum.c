#include <assert.h> /* assert */
#include <limits.h> /* INT_MAX */
#include <stdlib.h> /* EXIT_SUCCESS */

int main() {
    /* # Values */
    {
        /*
        You can choose the values explicitly.

        If you leave one out, it is the previous plus one.

        If the first is left out, it is `0`.

        - http://stackoverflow.com/questions/6434105/are-default-enum-values-in-c-the-same-for-all-compilers
        - http://stackoverflow.com/questions/24946699/enums-in-c-what-assumptions-can-be-made-about-the-value-of-the-underlying-varia?lq=1
        */
        {
            enum E {
                E0,
                E1,
                E2 = 3,
                E3,
                E4 = INT_MAX,
                /* ERROR: Overflow in enumeration values */
                /*E5*/
            };

            /* If unspecified, the first is 0. */
            assert(E0 == 0);
            assert(E1 == 1);
            assert(E2 == 3);
            /* Continue from the last one. */
            assert(E3 == 4);
            assert(E4 == INT_MAX);
        }

        /*
        # Value size

        # Value type

            Enum values are `int`.

            It does not seem possible to change that:

            - http://stackoverflow.com/questions/366017/what-is-the-size-of-an-enum-in-c
            - http://stackoverflow.com/questions/4879286/specifying-size-of-enum-type-in-c
            - http://stackoverflow.com/questions/18090541/how-to-set-the-value-of-an-enumeration-constant-outside-the-range-of-int
        */
        {
            /* sizeof */
            {
                enum E {E1, E2};
                assert(sizeof(enum E) == sizeof(int));
                assert(sizeof(E1) == sizeof(int));
            }

            /* The largest value that can be portably stored is INT_MAX. */
            /* http://stackoverflow.com/questions/366017/what-is-the-size-of-an-enum-in-c */
            {
                enum E {E1 = INT_MAX};
                /*enum E_BAD { E1 = INT_MAX + 1};*/
            }
        }
    }

    /* Declare enum variable. */
    {
        {
            enum E { E0, E1 };
            /* Like struct, you need enum. */
            enum E e = E1;
        }

        /* Typedef combo. No need to type enum everywhere. */
        {
            /* Multi line */
            enum E { E1, E2};
            typedef enum E E;
            E e;

            /* Single line */
            typedef enum F {g1, g2} F;
            F f;
        }
    }

    /* Nomemclature. */
    {
        enum E { E0 };
        /*
        # Enumerator

        # Member of an enum.

            Synonyms.
            Enumerator and "Member of an enum" are synonyms defined by the standard.
        */
    }

    /*
    ERROR: only const expressions allowed for initialition.

    When used, the values are constant expressions.
    */
    {
        const int i = 0;
        /*enum Constexpr { N = i };*/
        /*int is[N];*/

        /* This is why enum values don't generate variable size arrays. */
        {
            enum N { N =2 };
            int is[N];
            assert(sizeof(is) == 2 * sizeof(int));
        }
    }


    /* Enum constans are not lvalues. No const removal cast. */
    /*int *pe = &E1;*/

    /*
    # Count elements of an ENUM.

        Does not seem possible: http://stackoverflow.com/questions/2102582/how-can-i-count-the-items-in-an-enum

        Possible workaround: add an extra element and rely on the increasing order.

        Obvious downside: remote name conflict possibility.
    */
    {
        enum E {E1, E2, E_SIZE};
        assert(E_SIZE == 2);
    }
    return EXIT_SUCCESS;
}
