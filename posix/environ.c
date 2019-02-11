/* # environ
 *
 * Variable automatically set by POSIX libraries linked to.
 *
 * List of strings of type `VAR=val`.
 */

#include "common.h"

int main(void) {
    extern char **environ;
    char **env = environ;
    while (*env) {
        printf("%s\n", *env);
        env++;
    }
    return EXIT_SUCCESS;
}
