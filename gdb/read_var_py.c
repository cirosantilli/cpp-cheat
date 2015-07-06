/*
Local and global variables.
*/

#include <stdio.h>

int g = 1;

int main() {
    int i;
    float f;
    i = 1;
    f = 1.5;
    g++;
    i++;
    f += 1.0;
    printf("%d %d %f", g, i, f);
    return 0;
}
