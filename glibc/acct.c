/* # acct
 *
 * Write accounting information on process that start and end to given file.
 *
 * Given file must exist.
 *
 * Must be sudo to do it.
 *
 * Description of output under:
 *
 *     man 5 acct
 */

#include "common.h"

int main(void) {
    char *fname = "acct.tmp";
    if (creat(fname, S_IRWXU) == -1) {
        /* May fail because the file was owned by root. */
        perror("creat");
    }
    if (acct(fname) == -1) {
        perror("acct");
        /* May happen if we are not root. */
    }
}
