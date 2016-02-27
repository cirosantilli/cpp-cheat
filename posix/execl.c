/*
Canonical fork + execl + wait sequence.

This is run by Bash every time you hit enter:
http://stackoverflow.com/questions/6834487/what-is-the-variable-in-shell-scripting/31649402#31649402

# execl

# execlp

# execsle

# execv

# execvp

# execvpe

    Interfaces for `execve` system call.

    Execute and *leave*, ends current process!

    Common combo: fork + execl.

    This is effective because of COW implemented on some systems:
    memory will only be copied to new process if needed, and in this case it is no needed.

    Takes variable number or args.

    Must end null terminated.

    Versions:

    - char 'p': path, uses PATH var to find executable
    - TODO: char 'v', char 'e'? what's the difference?
*/

#include "common.h"

int main() {
    int status;
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        assert(false);
    } else if (pid == 0) {
        /*
        The fist argument is the program call by convention.

        This is not enforced however.
        */
        execl("./true", "./true", (char *)NULL);
    }
    wait(&status);
    if (WIFEXITED(status)) {
        assert(WEXITSTATUS(status) == EXIT_SUCCESS);
    } else {
        perror("execl abnormal exit");
        /* TODO: this fails. */
        /*assert(false);*/
    }
    return EXIT_SUCCESS;
}
