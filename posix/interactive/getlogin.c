/* # getlogin
 *
 * Get login name of controlling terminal
 *
 * This is different from `getuid` since it looks at the controlling terminal,
 * and not at processes specific information.
 *
 * Observe the difference with:
 *
 *     sudo ./getlogin.out
 *
 * Which outputs the username of the non-sudo user.
 */

#include "common.h"

int main(void) {
    char *login;
    login = getlogin();
    if (login == NULL) {
        perror("getlogin");
    } else {
        printf("%s\n", login);
    }
    return EXIT_SUCCESS;
}
