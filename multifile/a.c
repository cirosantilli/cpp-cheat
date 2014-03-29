#include <stdio.h>

#include "a.h"

// ERROR already defined in main.
//int i = 0;

// OK: only visible to this file.
static int staticInt = 0;

// Define externInt. Will store this initial value on the executable.
int externInt = 0;

// WARN: extern initialized.
// It does not make much sense to add extern to a definition: only to a declaration.
//extern int externIntInt = 1;

// ERROR redefinition:
//void func(){ puts("mainFunc"); }

static void staticFunc() {
    printf( "a#staticFunc:\n"                   );
    printf( "  staticInt   = %d\n", staticInt   );
    printf( "  aHStaticInt = %d\n", aHStaticInt );
    printf( "  externInt   = %d\n", externInt   );
    puts("");
}

void a() {
    // Static
        staticFunc();
        staticInt++;
        aHStaticInt++;
        externInt++;
}
