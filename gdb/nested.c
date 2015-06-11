/*
Stack trace tests: bt, f, whe
*/

#include <stdio.h>

int f0(int i) {
    return i + 1;
}

int f1(int i) {
    return f0(i + 1);
}

int f2(int i) {
    return f1(i + 1);
}

int f3(int i) {
    return f2(i + 1);
}

int main() {
    printf("%d\n", f3(0));
    return 0;
}
