#include <stdio.h>

/* Link time error: already defined in main. */
/*int main_func() { puts("si"); }*/

/* OK: only declared, not defined. Will use the one in main. */
int main_func(void);

/* OK: only visible to this file. */
static int static_func(void) {
    return 0x100;
}

int notmain_add(void) {
    return static_func() + main_func();
}
