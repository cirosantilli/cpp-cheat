/*
# array

    C arrays are simply lots of values put side by side on memory.

    Because they are side by side, it is simple to get the nth value
    quickly (random access), unless like, say, a linked list, in which
    you have to go follow lots of links before you reach the searched value.
*/

#include "common.h"

void print_array(int **mat, int m, int n) {
    int i, j;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

int main(void) {
    /* Basic example. */
    {
        int is[3];
        is[0] = 0;
        is[1] = 1;
        is[2] = 2;
        assert(is[0] == 0);
        assert(is[1] == 1);
        assert(is[2] == 2);
    }

    /*
    # Create arrays

    # Initialize arrays
    */
    {
        /*
        Size only.
        */
        {
            int is[2];
            assert(sizeof(is) == 2 * sizeof(int));
            /* Values undetermined since auto storage. */
            /*assert(is[0] == 0);*/
            /*assert(is[1] == 0);*/
        }

        /* With static storage however, initialization is guaranteed. */
        {
            static int is[2];
            assert(is[0] == 0);
            assert(is[1] == 0);
        }

        /* No size, only elements. */
        {
            int is[] = {0, 1, 2};
            assert(sizeof(is) == 3 * sizeof(int));
        }

        /*
        Both size and elements, less elements than size.

        TODO check remaining are guaranteed to be 0.
        */
        {
            int is[4] = {1, 2};
            assert(is[0] == 1);
            assert(is[1] == 2);
            assert(is[2] == 0);
            assert(is[3] == 0);

            /*
            But empty initializers are illegal. TODO rationale?

            http://stackoverflow.com/questions/17589533/is-an-empty-initializer-list-valid-c-code

            C++ allows them.
            */
            {
                /*int is[2] = {};*/
            }

            /*
            So to initialize to 0 you need this.

            http://stackoverflow.com/questions/2589749/initialize-array-to-0-in-c
            */
            {
                int is[2] = {0};
                assert(is[0] == 0);
                assert(is[1] == 0);
            }
        }

        /*
        More elements than size.

        WARN: array too small.

        TODO: what does the standard say should happen?
        */
        {
            /*int is[2] = { 1, 3, 2 };*/
        }

        /*
        ERROR no 0 size array

        Exists as a GCC extension.
        */
        {
            /*int is[0];*/
        }

        /* ERROR no negative sized array! */
        {
            /*int is[-1];*/
        }

        /*
        # Maximum array size possible

           http://stackoverflow.com/questions/9386979/the-maximum-size-of-an-array-in-c 

           It is unclear in the standard what happens if:

           - if you break `size_t`, as `sizeof` would fail.
           - `sizeof(void *)`

           As of 2015, no implementation can do this, since `size_t` is 2^64 which is too much memory.
        */

        /* Designated initializers are another method to initialize arrays not mentioned here. */
    }

    /*
    Access elements

        There is only one rule:

            a[b]

        is *exactly the same as:

            *(a + b).

        All the rest follows.
    */
    {
        /*
        TODO What type to use for indexes?

        http://stackoverflow.com/questions/3174850/type-for-array-index-in-c99

        - I think size_t is always enough
        - ptrdiff_t is not
        - uintptr_T I cannot say
        */

        /*
        # Negative index

            http://stackoverflow.com/questions/3473675/negative-array-indexes-in-c

            Perfectly legal, since:

                a[b] = *(a + b).

            and pointer arithmetic accepts negative values.
        */
        {
            int is[] = {1, 2};
            int *ip = &is[1];
            assert(ip[-1] == 1);
        }

        /*
        # Swap array name and index

        # 1[is]

            http://stackoverflow.com/questions/381542/in-c-arrays-why-is-this-true-a5-5a

            Obscure and confusing access syntax that you should
            never use except to surprise your friends.

            Perfectly legal because all we know is that:

                a[b] = *(a + b).

            If a is the int and b the pointer or the contrary
            does not matter: all that matters is that one is an int and the other a pointer.

        */
        {
            int is[] = {1};
            assert(0[is] == 1);
        }
    }

    /*
    Assign arrays.

    TODO why does it not work?
    */
    {
        int is[4]  = { 1, 2 };
        int is2[4] = { 1, 2 };
        /* ERROR incompatible pointer types. */
        /*is = is2;*/
    }

    /*
    # Get array length on compile time
    */
    {
        /* Only possible from the array, not from the pointer. */
        {
            /* From the array. */
            {
                int is[2];
                assert(sizeof(is) / sizeof(is[0]) == 2);
            }

            /* From the pointer: not possible. */
            {
                int is[2];
                int *p = is;
                assert(sizeof(p) == sizeof(int *));
            }
        }
    }

    /*
    # Set array length from a variable

        Before C99, array length had to be a compile time constant expression (C99 6.6):
        therefore you could not use variables for it, even `const` variables
        (which can be modified via typecasts).

        The two workarounds were:

        - enum
        - macros

        Sometimes you can also get away with `sizeof`, but this is limited.

        C99 introduces VLA which allows that, but may introduce a performace overhead.
        If the size is not a compile time constant expression, then the array
        automatically becomes a VLA.

        Bottomline: use enums. Macros have no scope, VLA has overhead.
    */
    {
        {
#if __STDC_VERSION__ < 199901L
            /* ERROR: cannot be initialized */
            /*
            int n = 2;
            int isVla[n] = { 1, 2 };
            */
#endif
        }

        {
            /* ERROR: cannot be initialized */
            /*
            const int n = 2;
            int isVla[n] = { 1, 2 };
            */
        }

        /* Enum. Seems to be the best general solution. */
        {
            {
                enum N { N = 3 };
                int is[N];
                assert(sizeof(is)/sizeof(is[0]) == 3);
            }

            /* Expressions involving enums are also fine. */
            {
                enum N { N = 3 };
                int is[N + 1];
                assert(sizeof(is)/sizeof(is[0]) == 4);
            }
        }

        /*
        sizeof works well when you want to copy the size of an existing array
        that had it size determined by the initialization.
        */
        {
            int is[] = {0, 1, 2};
            int is2[sizeof(is)/sizeof(is[0])];
            assert(sizeof(is2)/sizeof(is2[0]) == 3);
        }

        /*
        # Macro

            Shares the disadvantage of every macro of having no scope.

            Use enum instead.
        */
        {
#define DEFINESIZE 3
            int is[DEFINESIZE];
            is[2] = 1;
        }
    }

    /* # Arrays vs pointers */
    {
        /*
        Pointers and arrays are different types.

        (non-VLA) arrays have the size they are allocated to: they ARE the chunk.

        Pointers point to some chunk of memory.
        */
        {
            assert(sizeof(int*) != sizeof(int[3]));
            assert(sizeof(int[3]) == 3 * sizeof(int));
        }

        /*
        Almost any expression in which array identifiers appear decays to a pointer implicitly.

        sizeof is an exception.

        Here, (is + 1) makes is decay to an int* before the sizeof.
        */
        {
            int is[2];
            assert(sizeof(is + 1) == sizeof(int*));
        }

        /*
        # Address of arrays

            http://stackoverflow.com/questions/2528318/how-come-an-arrays-address-is-equal-to-its-value-in-c
        */
        {
            int is[2];
            assert(&is == (int(*)[2])is);
        }
    }

    /*
    # int []

        TODO Is this a type? is it different from int*?

        I think int[] is an incomplete type, and can only appear on function declarations,
        where it is identical to int*.
    */

    /*
    # Iterate array

        The only way is with the good and old for loop.

        No iterator magic, since no objects.
    */
    {
        int is[] = { 0, 1, 2 };
        int i;
        for (i = 0; i < sizeof(is)/sizeof(is[0]); i++) {
            printf("%d ",is[i]);
        }
    }

    /*
    # Bounds breaking

        No bound check is done to avoid overhead.

        Time to break down the program by making this access memory
        locations it should not try to access! =)

        Other less fun languages check those things and allow programs to avoid breakdown:
        C does not. You try to cheat your OS, and the OS kills you.

        The C standard specifies that such actions lead to unspecified behaviour.

        It may lead to Segmentation faults or not.

        Note however that this does not always happen, as a program may
        just access another location inside its legal memory address space
        but in a completelly unpredicatable manner, and the os has no way to it did this

        This leads to very hard to debug errors, but is inevitable if you want
        to avoid the overhead of checking arrays bounds on every dereference
    */
    {

        int is[2] = { 0, 1 };
        volatile int j;
        size_t i;

        /*
        GCC 4.7 is smart enough to warn agains this one.
        */
        {
            /*j = is[2];*/
        }

        /*
        GCC 4.7 is not smart enough to warn agains this one!

        May lead to segmentation faults, but this is unlikely.

        Unspecified behaviour.
        */
        if (0) {
            srand(time(NULL));
            i = rand() % 2;
            printf("overflow = %d\n", is[2 + i]);
        }

        /* This will almost certainly lead to a segmentation fault. */
        if (0) {
            for (size_t i = 0; i < SIZE_MAX; i++) {
                is[i] = 0;
                /*j = is[i];*/
            }
            assert(is[0] == 0);
        }
    }

    /*
    # Multidimentional arrays

        Before using them, always consider using single dimentional arrays,
        which are much simpler to handle with some multiplication and modulos.

        It is easier to explicily calculate indexes than to deal with the C
        type system.

        Cases where this would be a better design choice: TODO
    */
    {
        int *m1[2];
        int m11[] = { 1, 2, 3    };
        int m12[] = { 4, 5, 6, 7 };
        m1[0] = m11;
        m1[1] = m12;

        /* ERROR: cannot know    how much memory to allocate! */

            /*int m31[][3];*/

        /* Error: = {...} works only at declaration */

            /*int m111[2][3];*/
            /*m111[0] = &(int*[3]){1,2,3};*/

        /* Allocate the exact ammount: 2 pointeres to int[3]. */
        int m2[][3] = {
            { 1, 2, 3 },
            { 4, 5, 6 }
        };

        /* Allocate 3x3, fills only 2x3. The rest is 0 or m3[0] gets a NULL pointer? */
        int m3[3][3] = {
            { 1, 2, 3 },
            { 4, 5, 6 }
        };

        /*
        ERROR: last must be there.

        This is an array of m[3] arrays!!
        the data on an array is sequentially written to RAM
        and all of its elements have a fixed size (so they can be indexed!) 

        If you don't know the `sizeof(m[3])`, (and you don't know the sizeof(m[]!)) 
        you can't put all those m[3] sequentially on the RAM.

        The compiler could look at each element of the initialization
        and ensure they all have the *same size*, and then take that size, 
        but this would take a long time, so it just forces the user to input this 
        */
        {
            /*int m3[][] = {*/
                /*{ 1, 2, 3    },*/
                /*{ 4, 5, 6, 7 }*/
            /*}*/
        }

        /*
        Pass multidimentional arrays to functions.

        Never do that: pass an array, give m and n and do some operations instead.
        */
        {
            puts("\npass multidim to func:");
            enum { mc = 2 };
            /* Two int pointers. */
            int* mat[mc];
            int mat1[][3] = {
                { 1, 2, 3 },
                { 4, 5, 6 }
            };
            int i;
            for (i = 0; i < mc; i++) {
                /* First points to the int at address 0 of the matrix mat1. */
                mat[i] = mat1[i];
            }
            print_array(mat, 2, 3);
        }

        /* Multidimentional > 2 */
        {
            int m4[][2][3] = {
                {{1, 2, 3}, {4 , 5,  6 }},
                {{7, 8, 9}, {10, 11, 12}}
            };
            /* Allocates exact amount for first: 2x2x2. */

            int m41[3][2][3] = {
                {{ 1, 2, 3}, {4 , 5,  6 }},
                {{ 7, 8, 9}, {10, 11, 12}}
            };
            /* Allocates one extra for first dimension */

            /* ERROR: only first can be empty: */
            /*
                int m4[][][2] = {
                {{1,2},{3,4}},
                {{5,6},{7,8}}
            };
            */

            enum {MC = 2, NC = 4};
            int m5[MC][NC];

            /*
            int m7[mc][nc] = {
                {1,2,3},
                {4,5,6}
            };
            */
        }

        /* Matrix pattern. */
        {
            int i, j;
            for (i = 0; i < 2; i++) {
                printf("\n");
                for(j = 0; j < 3; j++) {
                    printf("%d ", m1[i][j]);
                }
            }
            printf("\n\n");
        }
    }

    return EXIT_SUCCESS;
}
