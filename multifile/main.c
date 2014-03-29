#include <stdio.h>

// MUST come before the include.
// Preprocessor does things in the exact same order it sees them.
//#define DEF
#define DEF
#include "a.h"
#include "b.h"

int i = 0;
static int staticInt = 0;

static void staticFunc() {
    printf( "main#staticFunc:\n"                );
    printf( "  staticInt   = %d\n", staticInt   );
    printf( "  aHStaticInt = %d\n", aHStaticInt );
    printf( "  externInt   = %d\n", externInt   );
    puts("");
}

void func(){ puts( "mainFunc" ); }

int main(int argc, char** argv) {
    // Static demostration
        staticFunc();
        a();
        staticFunc();
        a();

    a();
    b();

    // Preprocessor includes
        def++;
}
