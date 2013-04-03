#include <stdio.h>

#define DEF
#include "a.h"
//#define DEF
    //ERROR def undefined
    //preprocessor does things in the exact same order it sees them

#include "b.h"

int i = 0;
static int staticInt = 0;

//extern int externIntInit = 1;
    //WARN
    //extern initialized?!

static void staticFunc()
{
    printf( "main"              );
    printf( "%d\n", staticInt   );
    printf( "%d\n", aHStaticInt );
    printf( "%d\n", externInt   );
}

void func(){ puts( "mainFunc" ); }

int main( int argc, char** argv )
{
    //static demostration
        staticFunc();
        a();
        staticFunc();
        a();

    a();
    b();

    //preprocessor includes
        def++;

    return 0;
}
