#include <stdio.h>

int f(int i, int j) {
    return i + j;
}

int main() {
    int i;
    int (*fp)(int, int);
    fp = f;
    i = (*fp)(1, 2);
    printf("%d\n", i);
    return 0;
}
