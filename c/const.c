/*
# const
*/

#include "common.h"

int* int_ptr_func_int_ptr(int *ip) {
    (*ip)++;
    return ip;
}

#if __STDC_VERSION__ >= 199901L
    void const_array_size_argument(int is[const]) {
        is[0] = 1;
        int j;
        /* Compilation ERROR: assignment of read-only parameter is: */
            /*is = &j;*/
    }
#endif

int main(void) {
    int i = 0;
    const int ic = 0;
    /* Same. */
    /*int const ic = 0*/
    const int ic2 = i;

    /*
    BAD.

    Legal and compiles without warning, but is bad since ic3 cannot get a value
    unless you typecast its pointer with a warning.

    consts should normally get a value at initialization time.
    */
    const int ic3;

    /* ERROR: assignment of read only variable ic. TODO Illegal or undefined?. */
    {
        const int ic = 0;
        /*ic = 1;*/
    }

    /*
    # Modify const through pointer cast

        Casting a const to a non-const through a pointer is legal.

        Modifying he const with the pointer is undefined behavior (C99 6.7.3.5).

        For this reason, const it does not generate compile time constant expressions (C99 6.6):
        the undefined behavior could be to change the value of the const.

        In particular, existing implementaions may or may not put `const` in read only memory,
        so that the undefined behavior may be a page fault.

        `gcc` for example puts global constants on the `.rodata` section of the elf output.

        In practice however it might work for local function variables,
        which are just on the stack or registers.

        Many compilers raise warnings or prevent compilation of such constructs. 

        In C++, discarding const is illegal, and const generates compile time constants.
    */
    {
        const int ic = 0;

#ifdef UNDEFINED_BEHAVIOUR
        /*
        WARN: initialization discards const qualifier from pointer type.

        Likely to work since local variable.
        */
        /*
        int *ip = &ic;
        *ip = 1;
        assert(ic == 1);
        */
#endif
    }

    /*
    # const pointers

        There are 3 types of const pointers:

        - `const X *` or `X const *`    : cannot change the data of the thing pointer points to
        - `X * const`                   : cannot change which thing the pointer points to
        - `const X * const` or `X const * const` : both of the above
    */
    {
        /* const int * */
        /* int const * */
        {
            int i = 0;
            int j = 0;

            const int *cip = &i;
            int const *icp = &i;

            /* Can change which opbject it points to. */

                cip = &j;
                icp = &j;

            /* ERROR: const * prevents from changing the data of the object pointed to */

                /**cip = 2;*/
                /**icp = 2;*/
        }

        /* int * const */
        {
            int i = 0;
            int j = 0;
            int *const ipc = &i;

            *ipc = 1;
            assert(i == 1);

            /* ERROR: cannot change what is being pointed to */

                /*ipc = &j;*/

            /*
            # Single line declaration of multiple const pointers

                Just like `*` must be repeated once per variable, `*const` must also be repeated.
            */
            {
                int i = 0;
                int *const ipc2, *const ipc3, *ipcBad;
                /*               ^^^^^^ */
                /*               must repeat the `iconst` for each variable declared! */

                i = 0;
                ipcBad = &i;
                *ipcBad = 1;
            }

            {
                const int ic = 0;

                /* WARN */
                /* Initialization discards const. */
                /* It would be possible to change the value of the const. */

                    /*int *const ipc = &ic;*/

                /* BAD: we changed the value! */

                    /**ipc = 1;*/
            }
        }

        const int* const cipc = &ic;

        const int cis2[2] = { 1, 2 };
        /* ERROR */
        /*cis2[0] = 1;*/

        /*
        # const pointers to pointers

            There are 7 possibilities at level 2 already!

            To not mix up:

            - const always applies to the pointer at its left.
            - if there is no such pointer, it applies to the data
        */
        {
            int const ** icpp;
            int * const * ipcp;
            int ** const ippc;

            int const * const * icpcp;
            int const ** const icppc;
            int * const * const ipcpc;

            int const * const * const icpcpc;
        }

            /*
            # add const is not possible

                `const int * = int *` is possible, but it is not possible to do `const int ** = int **`.

                This is a bit counter-intuitive at first since:

                -   we feel like we are adding a `const` qualifier increases restrictoins.

                    However, when it may lead to const modification, it is not acceptable.

                -   the phenomenon only appears at level 2 pointers to pointers, not with simple pointers

                Similar considerations apply to the `volatile` qualifier.

                http://stackoverflow.com/questions/1468148/initialization-between-types-const-int-const-and-int-is-not-allowed-why
            */
            {
                /* If `const int ** = int **` were possible then we could change constants. */
                {
                    int* p = 0;

                    /* (1) THIS cannot be done: `const int ** = int **` */
                    /*int const** pp = &p;    */

                    /*int const c = 123;*/

                    /* OK, &c is int const*, and *p is int const* lvalue. p points to c now! */
                    /**pp = &c;*/

                    /* OK: p is not const. We changed c! */
                    /**p = 666;*/
                }

                /* The problem only arises in multidimensional cases. */
                /* Here it is impossible to change a const. */
                {
                    int i = 0;
                    int const * p = &i;
                }
            }
    }

    /*
    # const struct
    */
    {
        /*
        The entire struct is const.

        Members of a const struct cannot be modified.
        */
        {
            struct s { int i; };
            const struct s s = { 1 };
            /* ERROR */
            /*s.i = 2;*/
        }

        /* Single members can be declared const. */
        {
            struct s {
                int i;
                const int j;
            };
            struct s s = { 0, 1 };
            s.i = 2;
            /* ERROR */
            /*s.j = 2;*/
        }

        /* Entire structs cannot be declared const. */
        {
            /* WARN: useless type qualifier */
            /*const struct s { int i; };*/
        }
    }

    /*
    # Return const from func

        - <http://stackoverflow.com/questions/8716330/purpose-of-returning-by-const-value>
        - <http://stackoverflow.com/questions/8406898/benefits-of-using-const-with-scalar-type-e-g-const-double-or-const-int?lq=1>
    */
    {
        /*
        USELESS

        There seem to be no noticeable effect of returning const for non pointer scalars.
        */
        {
            /*int_func();*/
            /*const_int_func();*/
        }

        /*
        For pointer types this has a noticeable effect
        */
        {
            /* OK */
            {
                int i = 0;
                (*int_ptr_func_int_ptr(&i)) = 2;
                assert(i == 2);
            }

            /* ERROR */
            {
                int i = 0;
                /*(*const_int_ptr_func_int_ptr(&i)) = 2;*/
                /*assert(i == 2);*/
            }
        }

        /*
        For structs this also has a noticeable effect.

        In C++ however there can be noticeable effect
        because the returned object may have a non-const function that changes it
        so that the following is possible:

            objFunc().nonConst();

        but the following would not be:

            constObjFunc().nonConst();
        */
        {
            /*struct_func*/
            /*const_struct_func*/
        }
    }

#if __STDC_VERSION__ >= 199901L
    /*
    # const in array size function argument

        Same effect as declaring `int *const`, but without cast to pointer.
    */
    {
        int is2[2];
        is2[0] = 0;
        const_array_size_argument(is2);
        assert(is2[0] == 1);
    }
#endif

    return EXIT_SUCCESS;
}
