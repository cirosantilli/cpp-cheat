/*
Array arguments
*/

#include "common.h"

#pragma GCC diagnostic ignored "-Wsizeof-array-argument"

int array_arg(int i[]) {
    return i[0] + i[1];
}

#if __STDC_VERSION__ >= 199901L
int array_arg_static(int is[static 2]) {
    assert(sizeof(is) == sizeof(int *));
    return is[0] + is[1];
}

int array_arg_static_size(int i, int is[static i]) {
    assert(sizeof(is) == sizeof(int *));
    return is[0] + is[1];
}

int array_arg_static_unused(int is[static 2]) {
    assert(sizeof(is) == sizeof(int *));
    return is[0];
}
#endif

int array_size_arg(int i[3]) {
    assert(sizeof(i) == sizeof(int *));
    return i[0] + i[1];
}

int pointer_arg(int *i) {
    return i[0] + i[1];
}

void func_string_abc(char s[]) {
    assert(strcmp(s, "abc") == 0);
}

void func_string_const_abc(char const s[]) {
    assert(strcmp(s, "abc") == 0);
}

void func_string_modify(char s[]) {
    s[0] = '0';
}

void func_array(int a[]){
    assert(a[0] == 1);
}

void func_array_modify(int a[]) {
    a[0] = -1;
}

struct func_struct { int i; };
void func_struct_1(struct func_struct s) {
    assert(s.i == 1);
}

int main(void) {
    /*
    # Array argument vs pointer argument

        http://stackoverflow.com/questions/5573310/difference-between-passing-array-and-array-pointer-into-function-in-c

        Function declaration with array arguments are exactly equivalent
        to corresponding pointer declarations.

        Even if a number is put there, it is meaningless.

        This is analogous to array to pointer decay in expressions.

        Therefore, always use pointers which is the more direct approach.
        Linus crucifying people because of that: https://lkml.org/lkml/2015/9/3/428

        The following are all the same.
    */
    {
        int i[] = {1, 2};
        assert(array_arg(i)      == 3);
        /* Sizes are simply ignored. */
        assert(array_size_arg(i) == 3);
        assert(pointer_arg(i)    == 3);

#if __STDC_VERSION__ >= 199901L
        /*
        # static array function argument

            Makes:

            - a minum size guarantee
            - NULL is not possible

            TODO: what happens if those are broken?

            sizeof is still the same as a pointer.

            Applications:

            - optimization
            - better warnings

            but functionally identical.

            TODO concrete optimization example.
        */
        {
            assert(array_arg_static((int[]){1, 2}) == 3);
            assert(array_arg_static_size(2, (int[]){1, 2}) == 3);

#ifdef UNDEFINED_BEHAVIOUR
            /*
            No warning as of GCC 5.3?
            clang yes it seems: https://hamberg.no/erlend/posts/2013-02-18-static-array-indices.html
            */
            assert(array_arg_static(NULL) == 0);

            /* UB I imagine... */
            array_arg_static((int[]){1});

            /* TODO confirm, UB or not? */
            array_arg_static_unused((int[]){1});
#endif
        }

        /*
        Asterisk argument for VLA [*].

        - http://stackoverflow.com/questions/17371645/why-use-an-asterisk-instead-of-an-integer-for-a-vla-array-parameter-of-a-f
        - http://stackoverflow.com/questions/7225358/prototype-for-variable-length-arrays
        */
        {
        }
#endif
    }

    /*
    # Pass string literals to functions

        It initializes the string on stack and then passes a pointer to it.

        String literals should only be passed to `const char *` arguments,
        since string literals cannot be modified, possibly leading to segfaults.

        Ideally, all calling functions that can receive such strings should be const.

        This is not however enforced by the compiler.
    */
    {
        func_string_abc("abc");
        func_string_const_abc("abc");
        /* Segfault. */
        /*func_string_modify("abc");*/
    }

#if __STDC_VERSION__ >= 199901L
    /*
    http://stackoverflow.com/questions/1269568/how-to-pass-a-constant-array-literal-to-a-function-that-takes-a-pointer-without

    Pass struct and array literals to function using C99 compound literals.

    Unlike string literals, array and struct literals can be modified.
    */
    {
        func_array((int[]){1});

        func_array_modify((int[]){1});

        int is[] = {1};
        func_array_modify(is);
        assert(is[0] == -1);

        func_struct_1((struct func_struct){.i = 1});
    }
#endif

    return EXIT_SUCCESS;
}
