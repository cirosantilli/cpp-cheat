/*
# sentinel

    http://stackoverflow.com/questions/2407605/c-warning-missing-sentinel-in-function-call 

    Gives a warning if missing NULL termination on vararg lists.

    Keep in mind that NULL in ANSI C may be either `0` or `(void *)0`

    GCC guarantees it to be the pointer, and requires the pointer for sentinel to work.

    Not possible to change the sentinel:
    http://stackoverflow.com/questions/7638365/on-creating-variadic-function-with-custom-sentinel-value
*/

#include "common.h"

void print_strings(const char* first, ...) __attribute__((sentinel));

void print_strings(const char* first, ...) {
    va_list ap;
    const char* tmp;
    if (!first)
        return ;
    printf("%s\n", first);
    va_start(ap, first);
    while (1) {
        tmp = va_arg(ap, const char*);
        if (tmp == 0)
            break;
        printf("%s\n", tmp);
    };
    va_end(ap);
}

int main() {
    print_strings("print_strings", "a", "b", "c", NULL);
    print_strings("print_strings", "a", "b", "c", (void *)NULL);

    /* WARN: missing sentinel. */
    /*print_strings("a", "b", "c");*/

    /* Nope, 0 does not work, need the pointer. */
    /*print_strings("a", "b", "c", 0);*/

    /*
    execl is a prototypical example of null termination of vararg..

    It is impemented as a GCC 5.2 built-in.
    */
    {
        /*execl("/usr/bin/env", "echo", "a", "b");*/
    }

    return EXIT_SUCCESS;
}
