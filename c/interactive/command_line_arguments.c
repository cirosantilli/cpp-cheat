/*
# Command line arguments

    Try running this as:

        ./command_line_arguments asdf qwer zxcv
*/

#include "common.h"

int main(int argc, char **argv) {
    int i;
    printf("argc = %d\n", argc);
    for (i = 0; i < argc; ++i) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }
    return EXIT_SUCCESS;
}
