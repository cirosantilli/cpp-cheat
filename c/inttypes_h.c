/*
# PRIxPTR
*/

#include "common.h"

int main() {
#if __STDC_VERSION__ >= 199901L
    /*
    # PRIxPTR

        0 pad pointers.

        To print pointers and line them up nicely,
        one must take into account that trailing zeroes are omitted.

        One option is to space pad:

            %10

        But this produces:

                0x10
            0x10000000

        which is still ugly.

        The ideal would then be to pad with zeros as in:

            0x00000010
            0x10000000

        The notation:

            %010p

        is not supported TODO why not?

        The solution to this introduced in C99 is to use `uintptr + PRIxPTR`:
        http://stackoverflow.com/questions/1255099/whats-the-proper-use-of-printf-to-display-pointers-padded-with-0s

        There seems to be no convenient way to take into account pointer sizes except defining thingg manually:
        For example, x32 uses 4 bytes, x64 8, etc.

    */
    {
        /* 2 for "0x" and one for trailing '\0'. */
        char s[PRIxPTR_WIDTH + 3];
        printf("PRIxPTR = %s\n", PRIxPTR);
        printf("PRIxPTR usage = %0*" PRIxPTR "\n", PRIxPTR_WIDTH, (uintptr_t)(void*)1);
    }

    /*
    # Fixed size integer printf format

    # PRId16

    # PRId32

    # PRId64

        Why not modify printf instead of adding those new macros?
        http://stackoverflow.com/questions/1183679/why-werent-new-bit-width-specific-printf-format-option-strings-adoped-as-pa

    # PRIu32

        Unsigned versions.
    */
    {
        printf("PRId16 = %s\n", PRId16);
        printf("PRId32 = %s\n", PRId32);
        printf("PRId64 = %s\n", PRId64);

        /* Samplel usage:*/
        printf("%" PRIx32 "\n", (uint32_t)0xFFFFFFFF);
    }
#endif
}
