/* https://stackoverflow.com/questions/16285623/pwd-to-get-path-to-the-current-file/54155296#54155296 */

#define _XOPEN_SOURCE 700
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
    long n;
    char *buf;

    n = pathconf(".", _PC_PATH_MAX);
    assert(n != -1);
    buf = malloc(n * sizeof(*buf));
    assert(buf);
    if (getcwd(buf, n) == NULL) {
        perror("getcwd");
        exit(EXIT_FAILURE);
    } else {
        printf("%s\n", buf);
    }
    free(buf);
    return EXIT_SUCCESS;
}
