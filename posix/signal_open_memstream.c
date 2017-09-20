/*
Attempt to malloc from signal handler with open_memstream:
https://stackoverflow.com/questions/3366307/why-is-malloc-not-async-signal-safe

Fails because it is not possible to convert FILE * to fd,
and write is async-signal safe while fwrite is not.
*/

#define _XOPEN_SOURCE 700
#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

volatile sig_atomic_t fd;

void signal_handler(__attribute__((unused)) int sig) {
    int i;
    for (i = 0; i < 1023; ++i)
        write(fd, "a", 1);
}

int main(void) {
    char *bufp;
    size_t sizep;
    FILE *fp;

    fp = open_memstream(&bufp, &sizep);
    fd = fileno(fp);
    if (fd == -1) {
        perror("fileno");
        /* Expected failure.*/
        return EXIT_SUCCESS;
    }
    signal(SIGALRM, signal_handler);
    assert(kill(getpid(), SIGALRM) == 0);
    fflush(fp);
    printf("%s\n", bufp);
    fclose(fp);
    free(bufp);
    return EXIT_SUCCESS;
}
