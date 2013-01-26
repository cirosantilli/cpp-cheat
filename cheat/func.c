#include <stdio.h>
#include <stdlib.h>

//ERROR no func overload in c
    //void overload(int n){}
    //void overload(float n){}

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
 
//UNPORTABLE: func in func. gcc
    //int fOut()
    //{
    //    int fIn(){ return 1; };
    //    return fIn();
    //}

int main(){

    int i = 0;
    int is[] = {0,1};

    //automatic conversions
        fInt(1.0);
        fFloat(1);

    //ERROR no func in func
        //void fInMain(){}

    //int *is2 = {0,1};
    //ERROR

    puts("static variable in functions");
        withStaticVar();
        //a = 2, sa = 2
        withStaticVar();
        //a = 2, sa = 3
    puts("");

    puts("func pointers");
        printf( "%d\n", intFuncIntInt(&addInt,2,1) );
        //3
        printf( "%d\n", intFuncIntInt(&subInt,2,1) );
        //1
    puts("");

    //func in func
        //printf("fOut() = %d",fOut());

    return EXIT_SUCCESS;
}
