#include <stdio.h>
#include <stdlib.h>

//functions tutorial

void f1 (int *i){}
void f2 (int i[]){}
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

int main(){

    int i = 0;
    int is[] = {0,1};

    //int *is2 = {0,1};
    //won't compile

    //array to function
    
    //static variable in functions
        withStaticVar();
        //a = 2, sa = 2
        withStaticVar();
        //a = 2, sa = 3

    //func pointers
        printf( "%d\n", intFuncIntInt(&addInt,2,1) );
        //3
        printf( "%d\n", intFuncIntInt(&subInt,2,1) );
        //1

    return EXIT_SUCCESS;
}
