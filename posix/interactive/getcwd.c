/* A pwd implementation. */

#include "common.h"

int main(void) {
    /* TODO don't hardcode. */
    enum Constexpr { N = 1 << 10 };
    char buf[N];
    if (getcwd(buf, N) == NULL) {
        perror("getcwd");
        exit(EXIT_FAILURE);
    }
    printf("%s\n", buf);
    return EXIT_SUCCESS;
}
