/*
# union

    Like struct, but all fields share the same data space.

    If there are several data sizes, the struct has the size of the largest.

    TODO applications:
    http://stackoverflow.com/questions/4788965/c-c-when-would-anyone-use-a-union-is-it-basically-a-remnant-from-the-c-only
*/

#include "common.h"

int main() {
    {
        union U {
            int i;
            int j;
        } u;
        u.i = 0;
        u.j = 1;
        assert(u.i == 1);
    }
    return EXIT_SUCCESS;
}
