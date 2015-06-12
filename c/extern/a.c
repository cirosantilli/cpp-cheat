#include <stdio.h>

int commonInt = 1;
int externInt = 1;

void printA() {
    commonInt++;
    externInt++;
    printf("commonInt = %d\n", commonInt);
    printf("externInt = %d\n", externInt);
}
