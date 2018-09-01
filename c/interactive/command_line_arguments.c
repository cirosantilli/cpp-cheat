/* # Command line arguments
 *
 * Try running this as:
 *
 *     ./command_line_arguments.out asdf qwer zxcv
 *
 * Output:
 *
 *     argc = 4
 *     argv[0] = ./command_line_arguments.out
 *     argv[1] = asdf
 *     argv[2] = qwer
 *     argv[3] = zxcv
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
