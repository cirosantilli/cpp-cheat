/*
http://stackoverflow.com/questions/8235436/how-can-i-monitor-whats-being-put-into-the-standard-out-buffer-and-break-when-a
http://stackoverflow.com/questions/1538463/how-can-i-put-a-breakpoint-on-something-is-printed-to-the-terminal-in-gdb
*/

#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    write(STDOUT_FILENO, "asdf1", 5);
    write(STDOUT_FILENO, "qwer1", 5);
    write(STDOUT_FILENO, "zxcv1", 5);
    write(STDOUT_FILENO, "qwer2", 5);
    printf("as");
    printf("df");
    printf("qw");
    printf("er");
    printf("zx");
    printf("cv");
    fflush(stdout);
    return EXIT_SUCCESS;
}
