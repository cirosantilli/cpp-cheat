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

int main() {
    {
        int is[3];
        is[0] = 0;
        is[1] = 1;
        is[2] = 2;
        assert(is[0] == 0);
        assert(is[1] == 1);
        assert(is[2] == 2);
    }

    {
        int is[] = { 0, 1, 2 };
        assert(is[0] == 0);
        assert(is[1] == 1);
        /* Allocates exact size. */
        assert(is[2] == 2);
        /* ERROR */
        /*is = {3,4,5};*/
    }

    {
        int is[4] = { 1, 2 };
        assert(is[0] == 1);
        assert(is[1] == 2);
        assert(is[2] == 0);
        assert(is[3] == 0);
    }

    {
        int is[4]  = { 1, 2 };
        int is2[4] = { 1, 2 };
        /* ERROR incompatible pointer types */
        /*is = is2;*/
    }

    /*WARN array too small*/
    {
        /*int is[2] = { 1, 3, 2 };*/
    }

    /* ERROR no negative sized array! */
    {
        /*int is[-1];*/
    }

    /*
    ERROR no 0 size array

    Possible as a gcc extension.
    */
    {
        /*int is[0];*/
    }

#if __STDC_VERSION__ >= 199901L
    /*
    # Designated initializer for arrays

        Allows to initialize array elements in any order.

        There is also a struct version.
    */
    {
        {
            int is[] = {
                [1] = 1,
                [0] = 0,
            };
            assert(is[0] == 0);
            assert(is[1] == 1);
        }

        /* Missing elements are zeroed. */
        {
            int is[2] = {
                [1] = 1,
            };
            assert(is[0] == 0);
            assert(is[1] == 1);
        }

        /*
        Multiple assignments for a single int.

        Only last takes effect.

        WARN -Woverride-init
        */
        {
            int is[1] = {
                [0] = 0,
                [0] = 1,
            };
            assert(is[0] == 1);
        }

        /* arrays of structs can refer multiple times to the same struct */
        {
            struct S { int i; int j; };

            struct S ss[] = {
                [0].i = 0,
                [0].j = 1,
                [1].i = 2,
                [1].j = 3,
            };

            assert(ss[0].i == 0);
            assert(ss[0].j == 1);
            assert(ss[1].i == 2);
            assert(ss[1].j == 3);
        }

        /*
        Mix designated and non designated initialization.

        Non designated pick off where the last designated left.

        Non specified ones are zero.
        */
        {
            {
                int is[4] = {
                    -1,             /* [0] */
                                    /* [1] was not specified, so it is 0. */
                    [2] = 1,
                    2,              /* [3], because it comes after [2] */
                };
                assert(is[0] == -1);
                assert(is[1] == 0);
                assert(is[2] == 1);
                assert(is[3] == 2);
            }

            /* possible to overwrite values */
            {
                int is[2] = {
                    0,          /* [0] first assign */
                    1,          /* [1] first assign */
                    [0] = 2,    /* [0] second assign, overwrites first */
                    3,          /* [1] because comes after [0], second assign, overwrites first */
                };
                assert(is[0] == 2);
                assert(is[1] == 3);
            }
        }
    }
#endif

    /*
    # 1[is]

        Obscure and confusing access syntax that you should
        never use except to surprise your friends.

        All that the standard says is that: a[b] = *(a + b).
        If a is the int and b the pointer or the contrary
        does not matter: all that matters is that one is an int and the other a pointer.

        This seems to have been left like this since it is easier to compile.

        http://stackoverflow.com/questions/381542/in-c-arrays-why-is-this-true-a5-5a
    */
    {
        int is[] = { 1, 3, 2 };
        assert(is[1] == 1[is]);
    }

    /*
    # Get array length on compile time
    */
    {
        int is[] = {0, 1, 2};
        assert(sizeof(is)/sizeof(is[0]) == 3);
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

    /* Array type madness. */
    {
        /* Pointers and arrays are different types. */
        {
            assert(sizeof(int*) != sizeof(int[3]));
            assert(sizeof(int[3]) == 3 * sizeof(int));
            /*
            # int []

                Is this a type? is it different from int*?
            */
        }

        /* Some operators like `+` implicly convert arrays to pointers to the same type. */
        {
            int is[2];
            assert(sizeof(is + 1) == sizeof(int*));
        }

        /*
        ERROR: declaration of `vs` as an array of voids.
        You cannot have an array of void: how many bytes should the compiler allocate?
        */
        {
            /*void vs[2];*/
        }

        /* ERROR: ou can't declare multidimentional arrays like that. */
        {
            /*int[2] iss[2];*/
        }
    }

    /* Locations in memory of an array. */
    {
        int is[3];
        puts("locations of array:");
        printf("(void*)is = %p\n",(void*)is);
        printf("(void*)&is[0] = %p\n",(void*)&is[0]);
        printf("(void*)&is[1] = %p\n",(void*)&is[1]);
        printf("(void*)&is[2] = %p\n",(void*)&is[2]);
    }

    /* Loop array. The only way is with the good and old for loop. */
    {
        int is[] = { 0, 1, 2 };
        int i;
        for (i=0; i < sizeof(is)/sizeof(is[0]); i++) {
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
