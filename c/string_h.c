/*
# string.h

    String and array operations.

    # str vs mem

        The `str` prefixed functions uses '\0' to see ther string ends
        so callers don't need to give lengths.

        Many of the functions exist both on `str` and `mem` forms,
        where the `mem` form also takes a size.
*/

#include "common.h"

int main(void) {
    /*
    # memcpy

        Copy one array into another.

        Potentially faster than a for loop like:

            for(i=0; i<3; i++){
                is2[i] = is[i];
            }

        Since in some architectures this can be implemented with more efficient instructions
        than a naive for, and your compiler may not be smart enough to optimize this if you use a for.

        If overlap, undefined behavior. Use memmove in that case.
    */
    {
        {
            int is[] = { 0, 1, 2 };
            int is2[sizeof(is)/sizeof(is[0])];
            memcpy(is2, is, sizeof(is));
            assert(memcmp(is, is2, sizeof(is)) == 0);
        }

#if __STDC_VERSION__ >= 199901L
        /* Compound literal copy. */
        {
            int is[3];
            memcpy(&is, &(int []){ 0, 1, 2 }, sizeof(is));
            assert(memcmp(is, &(int []){ 0, 1, 2 }, sizeof(is)) == 0);
        }
#endif
    }

    /*
    # memmove

        Same as memcpy, but overlap may happen, thus slower.
    */
    {
        int is[]  = { 0, 1, 2, 3, 4, 5 };
        int is2[] = { 0, 1, 0, 1, 2, 5 };
        memmove(is + 2, is, 3 * sizeof(int));
        assert(memcmp(is, is2, sizeof(is)) == 0);
    }

    /*
    # strcpy

        Copy one string (up to first '\0') into another location.

        If they overlap, undefined behaviour.

        Could be more efficient than a for loop since it could
        tell the compiler to use a better specialized instruction.
    */
    {
        char cs[] = "abc";
        char cs2[4];
        char cs3[1];

        strcpy(cs2, cs);
        strcpy(cs2, "abc");

        /* BAD: no born checking as always */
        /*strcpy(cs3, "abc");*/
    }

    /*
    # strlen

        Get string length (up to first '\0').
    */
    {
        char cs[] = "abc";
        assert(strlen(cs) == 3);
    }

    /*
    # strncpy

        strcpy with maximum chars to copy.
    */

    /*
    # memcmp

        Compare arrays like strcmp.

    # memcmp vs for loop

    # strcmp vs for loop

        memcmp may be is faster than for loop because
        the compiler may optimize it better.

        On x86, the naive optimization is:

            repe cmpsb

        but on GCC 4.8 for example it still uses the glibc as it is even faster!
        TODO how?

        One catch: float NaN.
    */
    {
        int is[]  = { 0, 1, 2 };
        int is2[] = { 0, 1, 2 };

        /* Compares addresses, not data! */
        assert(is != is2);

        assert(memcmp(is, is2, 3 * sizeof(int)) == 0);
        is[1] = 0;
        assert(memcmp(is, is2, 3 * sizeof(int)) < 0);
        is[1] = 2;
        assert(memcmp(is, is2, 3 * sizeof(int)) > 0);

#if __STDC_VERSION__ >= 199901L
        /* memcmp with compound literals. */
        {
            int is[] = { 2, 0, 1 };
            assert(memcmp(is, &(int [3]){ 2, 0, 1 }, 3 * sizeof(int)) == 0);
        }
#endif
    }

    /*
    # strcmp

        Compare two strings.
    */
    {
        /* Equality. */
        assert(strcmp("abc", "abc") == 0);

        /* Smaller. */
        assert(strcmp("abc", "dbc") < 0);

        /* Larger. */
        assert(strcmp("abc", "aac") > 0);

        /*
        Different lengths. '\0' is smaller than all.
        https://stackoverflow.com/questions/36518931/what-does-strcmp-return-if-two-similar-strings-are-of-different-lengths/47366149#47366149*/
        assert(strcmp("a", "abc") < 0);
    }

    /*
    # strncmp

        Like strcmp, but only check at most n bytes.
    */
    {
        assert(strncmp("abc", "abd", 2) == 0);

        /*
        Different lengths: I think this is guaranteed as C99 says:

        > characters that follow a null character are not compared
        */
        assert(strncmp("a", "abc", 5) < 1);
    }

    /*
    # strcat

        Concatenate two strings.
    */
    {
        char s1[5];
        strcpy(s1, "ab");
        char s2[] = "cd";
        strcat(s1, s2);
        assert(strcmp(s1, "abcd") == 0);
        assert(strcmp(s2, "cd"  ) == 0);
    }

    /*
    # memchr

        mem version of strchr.
    */

    /*
    # strchr

        Search for char in string.

        Return pointer to that char if found.

        Return NULL if not found.
    */
    {
        {
            char cs[] = "abcb";
            assert(strchr(cs, 'b') == cs + 1);
            assert(strchr(cs, 'd') == NULL);
        }

        /*
        Find all occurences of c in cs:
        there is no direct libc function for this.
        */
        {
            char cs[] = "abcb";
            char *cp;
            char c = 'b';
            int is[] = { 1, 3 };

            int i = 0;
            cp = strchr(cs, c);
            while (cp != NULL) {
                assert(cp - cs == is[i]);
                cp = strchr(cp + 1, c);
                ++i;
            }
        }
    }

    /*
    # strrchr

        Find last match of character in string.
    */
    {
        char cs[] = "abcb";
        assert(strrchr(cs, 'b') == cs + 3);
        assert(strrchr(cs, 'd') == NULL);
    }

    /*
    # strstr

        Find first match of string in string.

        glibc has `strcasestr` which ignores the case.

        There seems to be no general array analogue: glibc has a `memmem` extension.
    */
    {
        char cs[] = "abcabcd";
        assert(strstr(cs, "bc") == cs + 1);
        assert(strstr(cs, "bd") == NULL);
    }

    /*
    # strspn

        Return the length of initial string that only contains bytes in the second argument.

        Mnemonic: SPaN of character set.

    # strcspn

        Complement (negation) of strspn: find bytes not there.
    */
    {
        /* '0' is not in the accept set, so the length is 5 for "abcba". */
        assert(strspn("abcba0abc", "abc") == 5);
    }

    /*
    # split

        See strtok

    # strtok

        Split string at a given character sequence.

        http://en.cppreference.com/w/c/string/byte/strtok
    */

    /*
    # strerror

        Returns a readonly pointer to the description of the error with the given number:

            char * strerror(int errnum);

        Also consider perror if you want to print those error messages to stderr.
    */
    {
        printf("strerror(EDOM) = \"%s\"\n", strerror(EDOM));
    }

    /*
    # strcspn

        How many characters in s1 are there before the first character present in s2.
    */
    {
        assert(strcspn("ab01", "10") == 2);
        assert(strcspn("a0b1", "10") == 1);
    }

    /*
    # strpbrk

        Point to the first character in s1 that is in s2.
    */
    {
        char *s1 = "ab01";
        assert(strpbrk(s1, "10") - s1 == 2);
    }

    /*
    # memset

        Set memory block to a single value.

        Like memcpy, potentially more efficient than a for loop.
    */
    {
        char cs[] = "abcdef";
        memset(cs + 2, '0', 3);
        assert(strcmp(cs, "ab000f") == 0);
    }

    /*
    # strcoll

        String compare using locale.

        TODO understand.
    */
    {
        /* TODO example */
    }

    return EXIT_SUCCESS;
}
