/*
# Ugly grammar

    C allows for grammar obscenities to be compatible with a distant past.

    Here are some perfectly legal jewels. Don't compile with `-pedantic-errors`, only `-std=c99`.
*/

#include "common.h"

/* After you've removed -pedantic-errors. */
#define ON 0

#if ON
/* Empty declaration. */
int;

/* Declaration without type. */
a;
f(void);
int dec_arg_no_type(x, y)
{ return 1; }

/* Declaration-list function arguments in declaration. TODO should be illegal? */
int g(x, y);

/* Declaration-list function arguments in definition. */
int g(x, y)
    int x;
    int y;
{ return 1; }
#endif

int main(void) {
    return EXIT_SUCCESS;
}
