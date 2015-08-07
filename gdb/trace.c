#include <stdio.h>
#include <stdlib.h>

int f(int i) {
    return i + 1;
}

int main() {
    int i;
    for (i = 0; i < 4; i++) {
        printf("%d\n", f(i));
    }
    return EXIT_SUCCESS;
}
