#include <stdio.h>
#include <assert.h>

#include "f.h"

int main(int argc, char** argv) {
    int i;
    int j;
    float f;
    double d;
    int is2x2[2][2];

    /* Subroutine call. */
    i = 1;
    f = 1.0f;
    d = 1.0;
    /* You should pass matrix data *transposed* to fortran. */
    is2x2[0][0] = 0;
    is2x2[1][0] = 1;
    is2x2[0][1] = 2;
    is2x2[1][1] = 3;

    s_( &i, &f, &d, &is2x2[0][0]  );
    assert(i == 2);
    assert(f == 2.0f);
    assert(d == 2.0);
    assert(is2x2[0][0] == 0);
    assert(is2x2[1][0] == 1);
    assert(is2x2[0][1] == 2);
    assert(is2x2[1][1] == 3);

    /* Function call. */
    i = 1;
    j = f_(&i);
    assert(i == 2);
    assert(j == 2);

    return 0;
}
