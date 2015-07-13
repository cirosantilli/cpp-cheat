/*
Stack trace tests: bt, f, whe
*/

#include <stdio.h>

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
    i += f0_0(i);
    i += f0_0(i);
    i += f0_1(i);
    return i;
}

int main() {
    printf("%d\n", f0(1));
    return 0;
}
