#include <stdlib.h>

int is[] = {0, 1, 2, 3};
enum N { N = 4 };
int *ip;

int main() {
    /* http://stackoverflow.com/questions/1651682/how-to-watch-a-c-dynamic-array-using-gdb */
    ip = is;
    return EXIT_SUCCESS;
}
