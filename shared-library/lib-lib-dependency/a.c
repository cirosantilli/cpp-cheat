#include <stdio.h>

#include "a.h"
#include "b.h"

int a(void) {
    return b() + 1;
}
