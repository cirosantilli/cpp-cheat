/*
http://stackoverflow.com/questions/2388561/block-output-of-debugged-program-gdb/35460141#35460141
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
    fprintf(stderr, "hello world\n");
    return EXIT_SUCCESS;
}
