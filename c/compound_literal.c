/*
# compound literals

    Before C99 there were no literals for arrays, structs or unions,
    while literals existed for ints, chars and even strings (which are arrays of chars...)

    Compound literals are exactly that: literals for types that are made up of many smaller
    pieces, thus compounded.

    Great source: http://www.drdobbs.com/the-new-c-compound-literals/184401404
*/

#include "common.h"

void func_array(int a[]){
    assert(a[0] == 1);
}

struct func_struct { int i; };
void func_struct_1(struct func_struct s) {
    assert(s.i == 1);
}

int main() {
#if __STDC_VERSION__ >= 199901L
    /* Compound literals for arrays */
    {
        int *is;

        is = (int[2]){ 0, 1 };
        assert(is[0] == 0);
        assert(is[1] == 1);

        /* Reassign is to a new array. */
        /* Old memory becomes inaccessible. */
        is = (int[2]){ 2, 3 };
        assert(is[0] == 2);
        assert(is[1] == 3);

        /* The effect is the same as `int is[] = { 1 }`, */
        /* that is: fill with zeroes. */
        is = (int[2]){ 1 };
        assert(is[0] == 1);
        assert(is[1] == 0);

        /* Major application: pass initialized arrays and structs to functions. */
        {
            func_array((int[]){ 1 });
            func_struct_1((struct func_struct){ .i = 1 });
        }
    }

    /*
    Compound literals yield lvalues.

    It is possible to take the address of compound literals.

    Unlike string literals, array literals can be modified.

    This means that the compound literal is an unnamed stack variable,
    and takes stack space.
    */
    {
        int *ip;
        ip = &(int){1};
        ip[0]++;
        assert(*ip == 2);
    }

    /* Int useless examples */
    {
        int i;

        i = (int){1};
        assert(i == 1);

        i = (int){1} + (int){1};
        assert(i == 2);

        /* Any expression is fine */
        {
            i = 0;
            i = (int){i + 1};
            assert(i == 1);
        }
    }

    /*
    Scope of compound literals.

    Just like for normal variable declaration,
    compound literal memory can only be accessed in the scope in which it is declared.

    http://stackoverflow.com/questions/14955194/lifetime-of-referenced-compound-array-literals
    */
    {
        int *p;
        {
            p = (int[]){1, 2};
            assert(p[0] == 1);
        }
        /* BAD *p is undefined. */
        /*assert(p[0] == 1);*/
    }
#endif
    return EXIT_SUCCESS;
}
