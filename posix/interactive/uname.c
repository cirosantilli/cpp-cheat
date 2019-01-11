/* # uname
 *
 * Get information about the current computer using `uname`.
 *
 * Unsurprisingly, it is the same information given by the POSIX utility `uname`.
 * https://unix.stackexchange.com/questions/136959/where-does-uname-get-its-information-from/485962#485962
 */
#include "common.h"

int main(void) {
    struct utsname info;
    if (uname(&info) == -1) {
        perror("uname");
        exit(EXIT_FAILURE);
    }
    printf("sysname  = %s\n", info.sysname );
    printf("nodename = %s\n", info.nodename);
    printf("release  = %s\n", info.release );
    printf("version  = %s\n", info.version );
    printf("machine  = %s\n", info.machine );
    return EXIT_SUCCESS;
}
