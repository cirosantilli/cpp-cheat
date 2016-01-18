/*
# Comments

    Get removed by the preprocessor.
*/

#include "common.h"

int main() {
    /* Standard multi line comment. */
    /*
    assert(false);
    */

    /* A comment may contain `/ *`, but GCC warns with `-Wcomment`. */

#if __STDC_VERSION__ >= 199901L
    /*
    Double slash comment like in C++ were only introduced in C99.

    Be portable and don't ever use them.

    They are however a part of C++.
    */
    //assert(false);
#endif
    return EXIT_SUCCESS;
}
