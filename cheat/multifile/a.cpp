#include "a.h"

#include <iostream>

using namespace std;

//int i = 0;
    //ERROR already defined

static int staticInt = 0;

int externInt = 0;

//void func(){ cout << "mainFunc" << endl; }
    //ERROR
    //redefinition

static void staticFunc(){
    cout << "a" << endl;
    cout << staticInt << endl;
    cout << aHStaticInt << endl;
    cout << externInt << endl;
}

void a()
{
    //static
        staticFunc();
        staticInt++;
        aHStaticInt++;
        externInt++;
}
