/* # sysconf
 *
 * sysconf is POSIX, but glib adds further Linux specific extensions.
 */

#include "common.h"

int main(void) {
    /* Find the number of processors.
     * Seems not to be possible in POSIX:
     * http://stackoverflow.com/questions/2693948/how-do-i-retrieve-the-number-of-processors-on-c-linux
     *
     * - conf: configured on kernel.
     * - onln: online, that is currently running. Processors can be disabled.
     */
    {
        printf("_SC_NPROCESSORS_ONLN = %ld\n", sysconf(_SC_NPROCESSORS_ONLN));
        printf("_SC_NPROCESSORS_CONF = %ld\n", sysconf(_SC_NPROCESSORS_CONF));
    }

}
