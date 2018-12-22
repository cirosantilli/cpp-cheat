#include "notmain.h"

/* Link time error: already defined in main. */
#if 0
int main_i = 0;
#endif

/* OK: only declared, not defined. Will be marked as common,
 * and default to the one in main.
 */
extern int main_i;

/* Only visible to this file. */
static int static_i = 20;

void notmain_func(
    int *main_i_out,
    int *static_i_out,
    int *static_i_function_out
) {
    /* Very similar to static_i, but only visible inside this function. */
    static int static_i_function = 30;
    main_i++;
    static_i++;
    static_i_function++;
    *main_i_out = main_i;
    *static_i_out = static_i;
    *static_i_function_out = static_i_function;
}
