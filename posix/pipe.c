/* # pipe
 *
 * Create unnamed pipes.
 *
 * Very close to the Linux pipe system call.
 *
 * Differences from popen:
 *
 * -   does not use a shell, avoiding many of its problems
 *
 * -   uses two integer file descriptors, one for each end of the pipe,
 *        instead of ANSI C `FILE` typedef.
 *
 *     Therefore you manipulate pipes with file descriptor functions
 *     like `open` and `write` instead of ANSI C `fopen` family.
 *
 * This gives you more control over the operations, but is harder to setup.
 *
 * Typically used with fork + exec.
 */

#include "common.h"

int main(void) {
    /* Producer and consumer are the same process.
     *
     * Useless but a good simple example.
     */
    {
        char data_receive[] = "abc";
        char data_send[] = "123";
        int pipes[2];
        size_t nbytes;

        if (pipe(pipes) == -1) {
            perror("pipe");
            assert(false);
        }
        /* Send. */
        nbytes = write(pipes[1], data_send, sizeof(data_send));
        assert(nbytes == sizeof(data_send));

        /* Receive. */
        nbytes = read(pipes[0], data_receive, sizeof(data_send));
        do {
            nbytes += read(pipes[0], &data_receive[nbytes], sizeof(data_send) - nbytes);
        } while (nbytes < sizeof(data_send));
        assert(nbytes == sizeof(data_send));

        /* Compare. */
        assert(strcmp(data_send, data_receive) == 0);
    }

    /* Parent writes to child.
     *
     * This works because if ever read happens before, it blocks.
     */
    {
        int pipes[2];
        const char data_send[] = "123";
        char data_receive[] = "abc";
        size_t nbytes;
        pid_t pid;

        nbytes = 0;
        if (pipe(pipes) == -1) {
            perror("pipe");
            assert(false);
        }
        fflush(stdout);
        pid = fork();
        if (pid == -1) {
            perror("fork");
            assert(false);
        }
        if (pid == 0) {
            /* Child only. */
            /* If read happens before write, it blocks because there is no data. */
            do {
                nbytes += read(pipes[0], &data_receive[nbytes], sizeof(data_send) - nbytes);
            } while (nbytes < sizeof(data_send));
            assert(strcmp(data_send, data_receive) == 0);
            exit(EXIT_SUCCESS);
        }
        /* Parent only. */
        nbytes = write(pipes[1], data_send, sizeof(data_send));
        assert((size_t)nbytes == sizeof(data_send));
        int status;
        wait(&status);
        /* Parent only after child finished. */
        assert(status == EXIT_SUCCESS);
    }
    return EXIT_SUCCESS;
}
