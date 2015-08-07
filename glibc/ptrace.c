/*
*/

#include "common.h"

int main() {
    long orig_eax;
    if (fork() == 0) {
        /* Must be called on the child. */
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        puts("child");
        exit(EXIT_SUCCESS);
    }
    wait(NULL);
    orig_eax = ptrace(PTRACE_PEEKUSER,
                        child, 4 * ORIG_EAX,
                        NULL);
    printf("The child made a "
            "system call %ld\n", orig_eax);
    ptrace(PTRACE_CONT, child, NULL, NULL);
    return EXIT_SUCCESS;
}
