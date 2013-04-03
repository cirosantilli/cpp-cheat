#include <stdio.h>

#include "a.h"

//int i = 0;
    //ERROR already defined

static int staticInt = 0;

int externInt = 0;

//void func(){ puts("mainFunc"); }
    //ERROR
    //redefinition

static void staticFunc(){
    printf( "a" );
    printf( "%d\n", staticInt );
    printf( "%d\n", aHStaticInt );
    printf( "%d\n", externInt );
}

void a()
{
    //static
        staticFunc();
        staticInt++;
        aHStaticInt++;
        externInt++;
}
