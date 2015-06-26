/*
# string

    By convention, *C strings* are simply char arrays
    terminated by the null character.

    This convention is used throughout libc string functions,
    such as `printf`, `strcmp` and others
    so that you don't have to pass an additional size parameter to them
    (those functions stop operating when they see the first null char).

    Nothing prevents you from making a "string" that contains a null char,
    except that you will break a very well stabilised convention,
    and libc functions will not work properly with it...

    If you absolutely need a "string" with a null char, just use regular
    array functions to manipulate it, and pass string lengths around.
*/

#include "common.h"

int main() {
    /* Basic example. */
    {
        char cs[] = "abc";

        /* SAME: */
        /*char cs[] = { 'a', 'b', 'c', '\0' }*/

        assert(cs[0] == 'a' );
        assert(cs[1] == 'b' );
        assert(cs[2] == 'c' );
        assert(cs[3] == '\0');

        cs[0] = 'A';
        assert(strcmp(cs, "Abc") == 0);

        /* ERROR: you cannot assign a string to memory like this, */
        /* except at initialization */

            /*cs = "Abc";*/

        /* You probably want `strcpy`. */
    }

    /*
    # Iterate string
    */
    {
        /* Pointer version. */
        {
            char s[] = "abc";
            char s2[] = "ABC";
            char *cPtr;
            for (cPtr = s; *cPtr != '\0'; cPtr++){
                *cPtr = toupper(*cPtr);
            }
            assert(strcmp(s, s2) == 0);
        }
    }


    /* String initialization */
    {
        /*
        char * vs char[] initialization

        http://stackoverflow.com/questions/1704407/what-is-the-difference-between-char-s-and-char-s-in-c

        With *, it cannot be modified later. Implementations may store it in readonly memory.

        In Linux, this is either `.rodata` or directly on the `.text` segment.
        */
        {
            {
                char *s = "abc";
                assert(s[0] == 'a');
                /* Unefined behaviour. On Linux, segfault. */
                /*cs[0] = '0';*/
            }

            {
                char s[] = "abc";
                assert(s[0] == 'a');
                /* OK */
                s[0] = '0';
            }

            /* TODO why can't we do the same thing with integers? E.g.: */
            {
                /*int * is = {1, 3, 2};*/
            }
        }

        /*
        Parenthesis. Legal but ugly. GCC 4.8 gives an error with `-pedantic`.
        */
        {
            /*char s[] = ("abc");*/
        }
    }

    /*
    # String literals

        http://en.cppreference.com/w/c/language/string_literal
    */
    {
        /* Escape chars in string conts */
        {

            /*
            Octal byte string literals

            `\` followed by any digit.

            Remember that 3 octal digits can encode a byte,
            but that 400 is out of byte range.

            1 or 2 digits are also OK, although it is less readable and more error prone.
            */
            {
                assert(!strcmp("\1", "\x1"));
                assert(!strcmp("\11", "\x9"));
                assert(!strcmp("\141", "a"));
                assert(!strcmp("\200", "\x80"));
                /* Warning: out of range. TODO legal? */
                /*assert(!strcmp("\400", "\x80"));*/
            }

            /* Hexadecimal bytes. */
            {
                assert(!strcmp("\x61", "a"));

                /*
                WARNING: Hex escape out of range.

                Happens because f can be part of a hex literal,
                and C tries to put it together.

                TODO what happens exactly according to ANSI C?
                Undefined behaviour?
                */
                /*{ "\xfff"; }*/

                /*
                The solution is to either concatenate strings, or use another escape:
                */
                assert(strcmp("\xff""f", "\xff\x66") == 0);

                /* Chinese UTF-8. */
                puts(">>>\xe4\xb8\xad<<< zhong1, chinese for \"middle\" in utf8");
            }

            /*
            \0 is the NUL char, but you can't insert is directly on the literal,
            or else the string is interpreted to end there since C strigs are NUL terminated.
            */
            printf(">>>%c<<< NUL char\n", '\0');

            /* Double quotes. */
            assert(strcmp("\"", "\x22") == 0);

            /* Single quote. Likely exists for symmetry with character literals. */
            assert(strcmp("\'", "\x27") == 0);

            /* Backslash. */
            assert(strcmp("\\", "\x5c") == 0);

            /*
            WARNING: Unknown escape sequence. TODO what ANSI C says can happen?
            */
            /*assert(strcmp("\c", "\x0b") == 0);*/

            /* Alert. Your terminal may interpret this as a sound beep or not. */
            assert(strcmp("\a", "\x07") == 0);

            /* Backspace. */
            assert(strcmp("\b", "\x08") == 0);

            /* Feed */
            assert(strcmp("\f", "\x0c") == 0);

            /* New line */
            assert(strcmp("\n", "\x0a") == 0);

            /* Carriage return */
            assert(strcmp("\r", "\x0d") == 0);

            /* Tab */
            assert(strcmp("\t", "\x09") == 0);

            /* Vertical tab */
            assert(strcmp("\v", "\x0b") == 0);

            /* Famous extensions: \e GNU for ESC */
        }

        /* String literals may be concatenated */
        /* no spaces are implied. */
        {
            char cs[] = "ab" "cd";
            assert(strcmp(cs, "abcd") == 0);

            /* This cannot be done with variables, */
            /* but can be useful if you have a string that is defined in a macro: */
            {
#define STRING_AB "ab"
                char cs[] = STRING_AB "cd";
                assert(strcmp(cs, "abcd") == 0);
            }

            /* Another application is to break a long string literal over severl lines */
            /* no newline is implied: */
            {
                char cs[] = "ab"
                            "cd";
                assert(strcmp(cs, "abcd") == 0);
            }

            /* It is not possible to break a string literal on multiple lines. */
            /*
            {
                char cs[] = "ab
                            cd";
                assert(strcmp(cs, "abcd") == 0);
            }
            */
        }
    }

    return EXIT_SUCCESS;
}
