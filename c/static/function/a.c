#include <stdio.h>

/* Link time error: already defined in main. */
/*int i() { puts("si"); }*/

/* OK: only declared, not defined. Will use the one in main. */
void f(void);

/* OK: only visible to this file. */
static void sf() { puts("a si"); }

void a() {
    f();
    sf();
}
