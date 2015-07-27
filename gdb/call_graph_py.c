/*
Stack trace tests: bt, f, whe
*/

#include <stdio.h>

typedef int (*int_int)(int);

int f0_0_0(int i) {
    return i + 3;
}

int f0_0_1(int i) {
    return i + 2;
}

int f0_1(int i) {
    return i + 1;
}

int f0_0(int i) {
    i += f0_0_0(i);
    i += f0_0_1(i);
    i += f0_0_0(i);
    return i;
}

int f0(int i) {
    int_int ii = f0_0;
    i += f0_0(i);
    i += f0_0(i);
    i += f0_1(i);
    i += ii(i);
    return i;
}

int main() {
    printf("%d\n", f0(1));
    return 0;
}
