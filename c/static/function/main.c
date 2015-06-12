#include <stdio.h>

void a();

/* OK: only declared, not defined. Will use the one in main. */
void f() { puts("main i"); }

/* OK: only visible to this file. */
static void sf() { puts("main si"); }

void m() {
    f();
    sf();
}

int main() {
    m();
    a();
    return 0;
}
