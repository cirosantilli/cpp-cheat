#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

//void overload(int n){}
//void overload(float n){}
    //ERROR no func overload in c

void fInt(int i){puts("fInt");}
void fFloat(float f){puts("fInt");}

void fIntPtr (int *i){}
void fIntArr (int i[]){}

//exact same thing

void withStaticVar()
{
    int a = 1;
    static int sa = 1;
        //BAD
        //- not thread safe
        //- hard to understand

    a++;
    sa++;

    printf("a = %d, sa = %d\n", a, sa);
}

int addInt(int n, int m)
{
    return n+m;
}

int subInt(int n, int m)
{
    return n-m;
}

int intFuncIntInt(int (*functionPtr)(int, int), int m, int n)
{
    return (*functionPtr)(m, n);
}

//a pow b
int pow2(int a, int b)
{
     int res = 1;
     int i;
     for(i=0; i<b; i++){
     res = res*a;
     }
     return res;
}
 
//TODO does not work
float pow2f(float a, float b)
{
     float res = 1.f;
     float i;
     for(i=0; i<b; i++){
     res = res*a;
     }
     return res;
}

int main(){

    //automatic conversions
    {
        fInt(1.0);
        fFloat(1);
    }

    puts("static variable in functions");
    {
        withStaticVar();
            //a = 2, sa = 2
        withStaticVar();
            //a = 2, sa = 3
    }

    puts("func pointers");
    {
        assert( addInt != subInt );
        assert( intFuncIntInt(&addInt,2,1) == 3 );
        assert( intFuncIntInt(&subInt,2,1) == 1 );
    }

    //func in func
    {
        //UNPORTABLE
        //gnu extension
        //not standard
        //printf("fOut() = %d",fOut());
    }

    return EXIT_SUCCESS;
}
