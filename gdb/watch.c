/*
For testing how many lines some debugging commands show, e.g. `l`
*/

#include <stdio.h>

int i = 0;

int main() {
    i += 1;
    i += 2;
    i += 3;
    printf("%d\n", i);
    return 0;
}
