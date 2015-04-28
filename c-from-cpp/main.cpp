#include <iostream>
#include <assert.h>

#include "c.h"

int main(int argc, char** argv) {
    int i = c(1, 1.0);
    assert(i == 2);
    return 0;
}
