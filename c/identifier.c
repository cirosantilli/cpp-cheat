#include "common.h"

int main() {
    /*
    # Identifiers

        C99 6.2.1.1 "Scope of identifiers".

        Identifiers are names either for:

        - variables
        - functions
        - structs
        - struct members
        - enums
        - unions
        - macros
        - labels (for goto)

        Most identifiers are use defined, but C99 has one that is predefined: `__func__`.
    */
    {
        /* TODO examples of each. */
    }

    /*
    # Scope of identifiers

        C99 6.2.1.3-4 "Scope of identifiers".
    */
    {
        /*
        The following scopes exist:

        - file scope: global stuff outside any function
        - function scope: only for labels. They are not constrained by non-function blocks like braces {}.
        - block scope: surrounding braces, either of functions, if, or alone
        */
        {
            /* TODO */
        }

        /*
        You may define variables in that scope with the same names as external ones,
        but if you do so the external ones will become completely invisible
        */
        {
            int i = 0;
            {
                assert(i == 0);

                /*
                From now on, it is impossible to access the outer `i`
                from the inner scope.
                */
                int i = 1;
                assert(i == 1);
            }
            assert(i == 0);
        }
    }

    /*
    # Linkage of identifiers

        Three types:

        - external: marked as external, with no previous non-external declaration
        - internal: file scope or static
        - none
    */

    /*
    # Storage duration of objects

    # Lifetime of objects

        C99 6.2.4 "Storage duration of objects"

        There are 3 types:

        - `static`: initilized only once, and live for the entire program. Like static local variables.
        - `automatic`: local variables, live until the end of blocks: functions or `{}`.
        - `allocated`: `malloc`. Lives until you `free` it.
    */
    {
        /*
        # Dangling pointer from block scope

            Undefined behavior: the lifetime of `i` ends because of block C99 6.2.4 p.5.

            http://stackoverflow.com/questions/2759371/in-c-do-braces-act-as-a-stack-frame
        */
        {
            int *ip;
            {
                int i = 1;
                ip = &i;
            }
#ifdef UNDEFINED_BEHAVIOUR
            if (*ip != 1)
                printf("after lifetime: %d\n", *ip);
#endif
        }

        /*
        Undefined behaviour, because the rhs `i` is already the uninitilized inner `i`.
        */
        {
            int i = 1;
            {
                int i = i;

                /* Same as: */
                /*int i;*/
                /*i = i;*/

#ifdef UNDEFINED_BEHAVIOUR
                printf("i = i scope: %d\n", i);
#endif
            }
        }
    }

    /*
    # Name space of identifiers

        C99 6.2.3 "Name space of identifiers"

        Not like the C++ concept.

        C has the following identifiers in different namespaces:

        - tags of: enums, structs, and union
        - labels (of goto)
        - members of structs
        - the rest: called *ordinary identifiers*: variable, function names

        A single identifier can be used many times in a single scope
        if it belongs to different namespaces.

        Each namespace can be differentiated by the syntax of the language.

        In C++, tags are put in the same namespace as variables.
    */
    {
        /* tag */
        struct s {
            /* member of struct */
            int s;
        };

        /* Odinary */
        int s = 0;

        /* Label. */
s:
        s = 0;

        /* ERROR: conflicting types for. */
        /* Ordinary already defined. */
        /*float s;*/

        /* ERROR. */
        /* A struct is also an ordinary identifier. */
        /*struct s s;*/
    }

    /*
    Names of identifiers
    */
    {
        /*
        C99 6.4.2 "Lexical Elements > Identifiers"

        Allowed identifiers follow the regex: `_[a-Z0-9_]*`

        Furthermore, user-defined identifiers should not be the same as:

        - keywords
        - reserved identifiers
        - predefined identifiers

        There exist identifier extensions, e.g. GCC allows `$` in identifiers.
        */
        {
            /* ERROR name cannot start with digit, or C thinks it is an integer literal. */
            /*int 0a;*/
        }

        /*
        # Keywords

            C99 6.4.2

            C99 6.4.2.1 p.4 says:

            > When preprocessing tokens are converted to tokens during translation phase 7, if a
            preprocessing token could be converted to either a keyword or an identifier, it is converted
            to a keyword.

            So it is impossible to have an identifier that is the same as a keyword.

            Full list:

                _Alignas        auto      extern    short
                _Alignof        break     float     signed
                _Atomic         case      for       sizeof
                _Bool           char      goto      static
                _Complex        const     if        struct
                _Generic        continue  inline    switch
                _Imaginary      default   int       typedef
                _Noreturn       do        long      union
                _Static_assert  double    register  unsigned
                _Thread_local   else      restrict  void
                                enum      return    volatile
                                                    while
        */

        /*
        # Reserved identifiers for future use

            C99 7.3.1 specifies that:

            > All identifiers that begin with an underscore and either an uppercase letter
            or another underscore are always reserved for any use.

            > All identifiers that begin with an underscore are always reserved
            for use as identifiers with file scope in both the ordinary and tag name spaces.

            Those reservations exist so that the languge may be extended later by the standard.

            The following keywords that conflict with reserved identifiers were already introduced:

            -   introduced in C99:

                - `_Bool`
                - `_Complex`
                - `_Imaginary`

            -   introduced in C11:

                - `_Alignas`
                - `_Alignof`
                - `_Atomic`
                - `_Generic`
                - `_Noreturn`
                - `_Static_assert`
                - `_Thread_local`

            so the tendency of the standard is to use `_Upper_case` for new conflicts.

            For convience, C99 also defines simpler macros to some new identifiers and adds them to headers, e.g.:

            - `_Complex` and `complex` from `complex.h`
            - `_Noreturn` and `noreturn` from `stdnoreturn.h`

            This allows includers to override the macro with `#undef complex` if necessary.

            POSIX adds many further per header reserved names which it would be wise to follow even on ANSI C:
            http://pubs.opengroup.org/onlinepubs/9699919799/functions/V2_chap02.html section "The Name Space".
        */
        {
            /* May break any in future versions of the standard. */
            int _Not_yet_a_keyword;
            int __not_yet_a_keyword;

            /* Fine because not file scope but rather block scope. */
            int _not_yet_a_keyword;
        }

        /*
        Standard seems to say nothing of this edge case,
        since `_` is not followed by any letter TODO confirm

        Even though it is quite cryptic, it does get some usage as `gettext` call in GNU projects,
        which inspired Django internationalization.

        The Underscore Javascript library is another notable usage.
        */
        {
            int _ = 1;
            assert(_ == 1);
        }
    }

#if __STDC_VERSION__ >= 199901L
    /*
    # Predefined identifiers

        There is only one in C99: `__func__`.

    # __func__

        If inside a function, the name of that function.

        This is not a macro, since the preprocessor cannot know
        the current function name, because the preprocessor does not parse.
    */
    {
        assert(strcmp(__func__, "main") == 0);
    }
#endif

    return EXIT_SUCCESS;
}
