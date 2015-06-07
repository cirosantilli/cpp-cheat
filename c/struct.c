/*
# struct

    Application:

    - declare lots of data in one go

    - pass lots of data in one go to functions

    - avoid changing function signatures if you add a new field
        to your struct.
*/

#include "common.h"

int main() {
    struct S {
        int i;
        float f;
    };

    /* Initialize by order. */
    {
        struct S s = { 1, 1.0 };
        assert(s.i == 1);
        assert(s.f == 1.0);

        s.i = 2;
        s.f = 2;
        assert(s.i == 2);
        assert(s.f == 2.0);
    }

    /* Define and initialize at the same time. */
    {
        struct S {int i; int j;} s0 = {0, 1}, s1 = {2, 3};
        assert(s0.i == 0);
        assert(s1.i == 2);

        struct S s2 = {4, 5};
    }

#if __STDC_VERSION__ >= 199901L
    /*
    # Designated initializer for structs

        Allows to struc values by their name instead of order.

        Sources:

        - oracle tutorial with examples: <http://docs.oracle.com/cd/E19205-01/819-5265/bjazo/index.html>
    */
    {
        {
            struct S s = {
                .f = 1.0,
                .i = 1
            };
            assert(s.i == 1);
            assert(s.f == 1.0);
        }

        /* Can be mixed with array designated initializers. */
        {
            struct S { int a[2]; int i; };

            /* TODO GCC 4.8 warns mssing i for [0]. Bug? */
            struct S ss[] = {
                [0].a = {0, 1},
                [0].i = 2,
                [1].a[0] = 3,
                [1].a[1] = 4,
                [1].i = 5
            };

            assert(ss[0].a[0] == 0);
            assert(ss[0].a[1] == 1);
            assert(ss[0].i == 2);

            assert(ss[1].a[0] == 3);
            assert(ss[1].a[1] == 4);
            assert(ss[1].i == 5);
        }
    }
#endif

    /*
    # Empty struct

        invalid, but possible as a GCC extension.

        http://stackoverflow.com/questions/24685399/c-empty-struct-what-does-this-mean-do
    */
    {
        /*struct s {};*/
    }

    {
        /* Assignment only works for initialization, unless use a C99 compound literal. */
        {
            struct S { int i; };
            struct S s;
            /*s = { 1 };*/
            /*s = { .i = 1 };*/
        }

        /*
        # Compound literals for structs

            C99 compound literals allow to assign structs to struct literals.
        */
        {
            struct S { int i; int j; };

            {
                struct S s;
                s = (struct S){ 1, 2 };
                assert(s.i == 1);
                assert(s.j == 2);
            }

            {
                struct S s;
                s = (struct S){ .j = 2, .i = 1 };
                assert(s.i == 1);
                assert(s.j == 2);
            }
        }
    }

    /* Pointer to struct. */
    {
        struct S s;
        struct S* sp;

        sp = &s;

        /* equivalent `a->b` equals `(*a).b` */

            sp->i = 1;
            /*(*sp).i = 1;*/

        assert(s.i == 1);
    }

    /* Array of structs initialization. */
    {
        struct S {
            int i;
            int j;
        };

        /* Non-designated. */
        {
            struct S ss[] = {
                { 0, 1 },
                { 2, 3 },
            };

            assert(ss[0].i == 0);
            assert(ss[0].j == 1);
            assert(ss[1].i == 2);
            assert(ss[1].j == 3);
        }

#if __STDC_VERSION__ >= 199901L
        /* Designated. */
        {
            struct S ss[] = {
                { .j = 1, .i = 0 },
                { .j = 3, .i = 2 },
            };

            assert(ss[0].i == 0);
            assert(ss[0].j == 1);
            assert(ss[1].i == 2);
            assert(ss[1].j == 3);
        }
    }
#endif

    /*
    Array fields

        Array length must be specified.

        Allocates that many objects of the given type.
    */
    {
        {
            struct S
            {
                /* ERROR: */
                /*int is[];*/
                int is0[2];
                int is1[2];
            };

            struct S s = { { 0, 1 }, { 2, 3 } };
            assert(s.is0[0] == 0);
            assert(s.is0[1] == 1);
            assert(s.is1[0] == 2);
            assert(s.is1[1] == 3);

            /* Non-designated init. */
            {
                struct S ss[] = {
                    { { 0, 1 }, { 2, 3 } },
                    { { 4, 5 }, { 6, 7 } }
                };
                assert(ss[0].is0[0] == 0);
                assert(ss[0].is0[1] == 1);
                assert(ss[0].is1[0] == 2);
                assert(ss[0].is1[1] == 3);
                assert(ss[1].is0[0] == 4);
                assert(ss[1].is0[1] == 5);
                assert(ss[1].is1[0] == 6);
                assert(ss[1].is1[1] == 7);
            }

#if __STDC_VERSION__ >= 199901L

            /* Designated init. */
            {
                struct S ss[] = {
                    { .is0 = { 0, 1 }, .is1 = { 2, 3 } },
                    { .is0 = { 4, 5 }, .is1 = { 6, 7 } },
                };
                assert(ss[0].is0[0] == 0);
                assert(ss[0].is0[1] == 1);
                assert(ss[0].is1[0] == 2);
                assert(ss[0].is1[1] == 3);
                assert(ss[1].is0[0] == 4);
                assert(ss[1].is0[1] == 5);
                assert(ss[1].is1[0] == 6);
                assert(ss[1].is1[1] == 7);
            }

#endif

        }

        /* Works for strings. */
        {
            struct S
            {
                char cs[3];
                int i;
            };

            {
                struct S s = { .cs = "ab", .i = 1 };
                assert(strcmp(s.cs, "ab") == 0);
                assert(s.i == 1);
            }

            {
                struct S s = { "ab", 1 };
                assert(strcmp(s.cs, "ab") == 0);
                assert(s.i == 1);
            }

            /*struct S s = { "ab" };*/
        }
    }

    /* Substructure init: it all works as expected. */
    {
        struct S1 { int i; int j; };
        struct S0 { struct S1 s; };

        /* Non-designated init. */
        {
            struct S0 s = { { 1, 2 } };
            assert(s.s.i == 1);
            assert(s.s.j == 2);
        }

#if __STDC_VERSION__ >= 199901L

        /* Designated init. */
        {
            struct S0 s = {
                .s = {
                    .j = 2,
                    .i = 1
                }
            };
            assert(s.s.i == 1);
            assert(s.s.j == 2);
        }

#endif

    }

    /*
    # Incomplete types

        Incomplete types are types which only have a declaration but no definition.
    */
    {
        /*
        # struct that contains itself

        # Incomplete type cycles

            It is impossible to do the following, because that would create an infinite loop:

            -   each S contains one S. and one i.

            -   therefore the size of each S must be 2 ints:

                size of S + size of int =
                        1 +           1 =
                                        2

            -   but then the size of S must be 3 ints:

                    size of S + size of int =
                            2 +           1 =
                                            3

            -   and so on

            The solution is to store opaque pointers instead of the actual structs.
        */
        {
            /* ERROR: s has incomplete type. */
            {
                /*
                struct S {
                    struct S s;
                    int i;
                };
                */
            }

            /* ERROR: struct s1 undefined */
            {
                /*
                struct S0 { struct S1 s1; };
                struct S1 { struct S0 s0; };
                */
            }

            /* ERROR: s1 has incomplete type */
            {
                /*
                struct S1;
                struct S0 { struct S1 s1; };
                struct S1 { struct S0 s0; };
                */
            }
        }

        /*
        # Opaque pointers

            You can have pointers to incomplete types.

            Forward declaration of S1 makes it makes it alright.

            Such pointers are called opaque pointers.
            <http://stackoverflow.com/questions/3854113/what-is-an-opaque-value>

            A common usage pattern is:

            - declare the opaque type in the .h file
            - declare functions that use the opaque pointer in the .h file
            - defined the type and the functions in the .c file

            Now clients can only pass around pointers,
            and use the type through the functions you give them,
            but not access the fields they choose.

            This is a way to implement private member variables in C.

            `FILE` is widely used as an example of an opaque pointer, but it is not strictly opaque:
            ANSI does not say that you cannot instantiate it, and popular implementations
            have allowed that: ANSI only says nothing about it's fields,
            so using them makes your code non-standard. TODO confirm.
        */
        {
            {
                struct S1;
                /* storage size of s isn't known . */
                /*struct S1 s1;*/
                struct S1* s1;
            }

            {
                struct S1;
                struct S0 { struct S1* s1; };
                struct S1 { struct S0* s0; };
            }

            /*
            The type itself has already been defined inside the struct definition,
            so the following is fine.
            */
            {
                struct S { struct S* s; };
            }
        }
    }

    /* = Assigns fields one by one. */
    {
        struct S s  = { 1, 1.0 };
        struct S s2 = { 2, 2.0 };
        s = s2;
        assert(s.i == 2);
        assert(s.f == 2.0);
    }

    /* equality `==` does not exist. There have been failed proposals. */
    {
        struct S { int i; };
        struct S s  = { 1 };
        struct S s2 = { 1 };
        /*assert(s == s2);*/
    }

    /*
    Inequalities do not exist either: `<` `>` `<=` `>=`

    Possible rationale: if `s.a < s2.a` and `s.b > s2.b`, what does `s < s2` eval to?
    */

    /*
    # struct size

        The way data is packed in a struct is not specified in the standard

        Common compiler strategy: align data to 32 bits
        which makes acess faster, using slightly more memory.
    */
    {
        struct S {
            char c;
            int i;
        };

        /* likelly to be 8 on a 2013 32 bit machine: */
        printf("struct sizeof = %zu\n", sizeof(struct S));

        assert(sizeof(char) + sizeof(float) <= sizeof(struct S));
    }

    /*
    # Unnamed struct

        This is a different concept than *anonymous structs*!!
        http://stackoverflow.com/questions/14248044/are-anonymous-structs-standard-and-really-what-are-they

        It is possible to create structs which don't have a name.

        Only the structs declared immediatiely after definition can be used.

        In theory only standardized in C11, but I am yet to be able to make GCC generate a warning.
        even with `-std=89 -pedantic -Wall`.

        <http://stackoverflow.com/questions/14248044/are-anonymous-structs-standard-and-really-what-are-they>
    */
    {
        /* Basic. */
        {
            struct { int i; int j; } s;
            s.i = 0;
            assert(s.i == 0);
        }

        /* Initialize. */
        {
            struct { int i; int j; } s = {0, 1};
            assert(s.i == 0);
            assert(s.j == 1);
        }

        /* Initialize array good style. */
        {
            struct { int i; int j; } s[] = {{0, 1}, {2, 3}};
            assert(s[0].i == 0);
            assert(s[0].j == 1);
            assert(s[1].i == 2);
            assert(s[1].j == 3);
        }

        /*
        Initialize array bad style.

        Generates a warning on GCC 4.7 and is horrible to read.
        */
        {
            /*struct { int i; int j; } s[] = { 0, 1, 2, 3 };*/
            /*assert(s[0].i == 0);*/
            /*assert(s[0].j == 1);*/
            /*assert(s[1].i == 2);*/
            /*assert(s[1].j == 3);*/
        }

#if __STDC_VERSION__ >= 201112L
        /*
        # Anonymous substructure and union

            Different from unnamed struct!
            <http://stackoverflow.com/questions/14248044/are-anonymous-structs-standard-and-really-what-are-they>

            Is an unnamed struct inside another struct.

            Is / was also the non-standard name given to some concept.

            TODO application?
        */
        {
            struct S {
                int i;
                struct {
                    int j;
                    int k;
                };
            };
            /* ERROR: missing braces */
            /*struct S s = {1, 2, 3};*/
            struct S s = {1, {2, 3}};
            assert(s.i == 1);
            assert(s.j == 2);
            assert(s.k == 3);
        }
#endif
    }

    /*
    # typedef struct combo

        Advantages:

        -   avoid typing struct all over

        -   if in the future you decide to change a struct,
            e.g. to an `int` with boolean flags, you can do it.

            This is because it prevents people from writing `struct S`
            with the `struct` keyword, and forces them to write just `struct`.

        -   write the identifier only 2 times instead of 3

        -   put all declaration information into one single place.
            No more "Should the typedef be before or after?" doubts.

        TL;DR best practice: whenever possible use:

            typedef struct {} S;

        Unfortunately this cannot be done if you need to declare the struct elsewhere to:

        -   you use a pointer to a struct of the same type inside it.
            E.g.: linked lists.

            In that case, use:

        -   use the declaration across many files. The typedef declaration would go into a `types.h`,
            and the definition on a `precise-topic.h`.
    */
    {
        /*
        The typedef can come before the struct.
        */
        {
            struct S {
                int i;
            };
            typedef struct S T;

            struct S s = {1};
            T t = {1};
            assert(s.i == t.i);
        }

        /*
        You can typedef and declare the struct in a single statement.
        */
        {
            typedef struct S {
                int i;
            } T;

            /* Same as: */
            /*
            typedef struct S T;
            struct S {
                int i;
            };
            */

            T t = {1};
            T *tp = &t;
            assert(tp->i == 1);

            struct S s = {1};
            struct S* sp = &s;
            assert(sp->i == 1);
        }

        /*
        The typedef and the struct can have the same name.

        So the common C89 pattern is `typedef struct S {...} S`.

        C11 adds anonymous structs which is even better.
        */
        {
            typedef struct S {
                int i;
            } S;

            struct S ss = {1};
            S s = {1};
            assert(ss.i == s.i);
        }

        /*
        # typedef to an unamed struct

            - type even less than for typedef struct
            - prevent anyone from using the useless `struct S`
            - DRYer
        */
        {
            {
                typedef struct {
                    int i;
                } TypedefUnnamed;
                TypedefUnnamed s = {1};
                TypedefUnnamed* sp = &s;
                assert(sp->i == 1);

                /* ERROR: storage size of `t` isn't known. */
                /* Same error as when the struct is not defined. */
                /* Awesome, users cannot shoot themselves on the foot! */

                    /*struct TypedefUnnamed t;*/
            }

            /* Does not work either if the typedef is needed inside the definition. */
            {
                /*
                typedef struct {
                    TypedefUnnamed* other;
                } TypedefUnnamed;
                */

                /* In that case you need: */
                {
                    typedef struct TypedefUnnamed TypedefUnnamed;
                    struct TypedefUnnamed {
                        TypedefUnnamed* other;
                    };
                }

                /* Or: */
                {
                    typedef struct TypedefUnnamed {
                        struct TypedefUnnamed* other;
                    } TypedefUnnamed;
                }

                /*
                TODO possible to make it work such that it is impossible to say `struct s`,
                like with unnamed structs?
                */
            }
        }
    }

    /*
    # bitfields

        Gives support for fields which contain a single bit in the language.
    */
    {
        struct S {
            unsigned b1 : 1;
            unsigned b2 : 2;
            unsigned b3 : 3;

            /* padding untill next int is added automatically because */
            /* next data is not a bitfield and accesses is faster if it is aligned */

                int i;

            unsigned b4 : 1;

            /* manually adds padding untill next field */
            /* even if it is a bitfield */

                unsigned : 0;

            unsigned b5 : 1;
        } s ;

        assert(sizeof(struct S) == 16);

        s.b1 = 1;
        assert(s.b1 == 1);

        /* WARN */
        /* overflow */
        /* truncate */
        /*s.b1 = 2;*/

        int i = 2;
        s.b1 = i;
        assert(s.b1 == 0);

        /* Only takes lsb. */
        i = 3;
        s.b1 = i;
        assert(s.b1 == 1);
    }

    /*
    # offsetof

        get distance of member variable from the start of the struct

        Appliction: get the struct that corresponds to a given pointer to a field.
        this is used in the kernel via `container_of`, and can be used to implement
        linked lists in ANSI C:
        http://stackoverflow.com/questions/10269685/kernels-container-of-any-way-to-make-it-iso-conforming
    */
    {
        struct foo {
            char a;
            char b[2];
            int c;
            char d;
        };

        printf("offsetof(struct foo, a) = %zu\n", offsetof(struct foo, a));
        printf("offsetof(struct foo, b) = %zu\n", offsetof(struct foo, b));
        printf("offsetof(struct foo, c) = %zu\n", offsetof(struct foo, c));
        printf("offsetof(struct foo, d) = %zu\n", offsetof(struct foo, d));
    }

    return EXIT_SUCCESS;
}
