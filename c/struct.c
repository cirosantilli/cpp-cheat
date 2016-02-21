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
    /* Basic struct definition. */
    struct S {
        int i;
        float f;
    };

    /*
    # Empty struct

        Invalid, but possible as a GCC extension.

        http://stackoverflow.com/questions/24685399/c-empty-struct-what-does-this-mean-do
    */
    {
        /* ERROR */
        /*struct S {};*/
    }

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

    /*
    Initialization with less members than the total.
    http://stackoverflow.com/questions/11152160/initializing-a-struct-to-0

    Fine: missing fields get the same value as they would have
    if they were static storage duration objects, thus 0 for int.
    */
    {
        struct S {int i; int j;};
        struct S s0 = {1};
        assert(s0.i == 1);
        assert(s0.j == 0);

        /* empty braces for initialization: GNU extension. */
        {
            /*struct S s0 = {};*/
        }
    }

    /* Define and initialize at the same time. */
    {
        struct S {int i; int j;} s0 = {0, 1}, s1 = {2, 3};
        assert(s0.i == 0);
        assert(s1.i == 2);

        struct S s2 = {4, 5};
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
            struct S {
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
    # Unnamed struct

        This is a different concept than *anonymous structs*!!
        http://stackoverflow.com/questions/14248044/are-anonymous-structs-standard-and-really-what-are-they

        It is possible to create structs which don't have a name.

        Only the structs declared immediatiely after definition can be used.
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

        TL;DR best practice: whenever possible use:

            typedef struct {} S;

        Some people, notably the Linux kernel, disagree:
        http://stackoverflow.com/questions/252780/why-should-we-typedef-a-struct-so-often-in-c

        Advantages:

        -   avoid typing struct all over

        -   if in the future you decide to change a struct,
            e.g. to an `int` with boolean flags, you can do it.

            This is because it prevents people from writing `struct S`
            with the `struct` keyword, and forces them to write just `struct`.

        -   write the identifier only 2 times instead of 3

        -   put all declaration information into one single place.
            No more "Should the typedef be before or after?" doubts.

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
            typedef struct S T;
            struct S {
                int i;
            };

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

        A common C89 pattern is `typedef struct S {...} S`.
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

    return EXIT_SUCCESS;
}
