/*
# static local

    It is as if the variable were a global.

    Use with caution:

    - hard to understand
    - not thread safe

    Advantage: scope restricted to a single function.

    It is like a "function private".
*/

#include "common.h"

void f(int *i_out, int *si_out) {
    int i = 0;

    /* static initialization is evaluated only once */
    /* the first time this function is called */
    static int si = 0;

    i++;
    si++;
    *i_out = i;
    *si_out = si;
}

int main() {
    int i;
    int si;

    f(&i, &si);
    assert(i == 1);
    assert(si == 1);

    f(&i, &si);
    assert(i == 1);
    assert(si == 2);

    return EXIT_SUCCESS;
}
