/* Sleep for one second.
 *
 * Used at:
 * https://stackoverflow.com/questions/556405/what-do-real-user-and-sys-mean-in-the-output-of-time1/53937376#53937376
 */

#define _XOPEN_SOURCE 700
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    sleep(1);
    return EXIT_SUCCESS;
}
