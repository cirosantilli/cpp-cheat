/* Tiny ls implementation that lists cwd. */

#include "common.h"

int main(void) {
    DIR* dp;
    struct dirent* entry;

    dp = opendir(".");
    if (dp == NULL) {
        perror("opendir");
        assert(false);
    }
    while ((entry = readdir(dp)) != NULL) {
        printf("%s\n", entry->d_name);
    }
    return EXIT_SUCCESS;
}
