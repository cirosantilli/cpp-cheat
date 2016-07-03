/*
# environ

    Automatically set by POSIX libraries linked to.

    List of strings of type `VAR=val`.
*/

#include "common.h"

int main(void) {
    /* Print entire environment. */
    extern char **environ;
    char **env = environ;
    char *s = "HOME=";
    while (*env) {
        if (!strncmp(*env, s, strlen(s))) {
            printf("%s\n", *env);
            break;
        }
        env++;
    }
    return EXIT_SUCCESS;
}
