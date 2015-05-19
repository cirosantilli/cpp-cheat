#include <stdio.h>

#include "a.h"

int i = 0;
static int staticInt = 0;

static void staticFunc() {
    printf( "main#staticFunc:\n"                );
    printf( "  staticInt   = %d\n", staticInt   );
    printf( "  aHStaticInt = %d\n", aHStaticInt );
    printf( "  externInt   = %d\n", externInt   );
    puts("");
}

struct s {
    int i;
};

int main(int argc, char** argv) {
    staticFunc();
    a();
    staticFunc();
    a();
    return 0;
}
