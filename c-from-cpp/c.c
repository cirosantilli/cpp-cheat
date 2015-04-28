#include <stdio.h>

#include "c.h"

int c(int i, float f) {
    printf( "c(int,float): %d, %f\n", i, f);
    return i + 1;
}
