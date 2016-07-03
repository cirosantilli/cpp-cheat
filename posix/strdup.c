/*
# strdup

    malloc-copy string.
*/

#include "common.h"

int main(void) {
    char *s = "abc";
    char *s2;
    s2 = strdup(s);
    s2[0] = '0';
    assert(strcmp(s,  "abc") == 0);
    assert(strcmp(s2, "0bc") == 0);
    free(s2);
    return EXIT_SUCCESS;
}
