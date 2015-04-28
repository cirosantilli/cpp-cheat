#include <stdio.h>

/* MUST come before the include. */
/* Preprocessor does things in the exact same order it sees them. */
/*#define DEF*/
#define DEF
#include "a.h"
#include "b.h"

int main(int argc, char** argv) {
    a();
    b();

    /* Preprocessor includes */
    def++;
}
