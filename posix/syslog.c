/* # syslog
 *
 * http://pubs.opengroup.org/onlinepubs/007904975/functions/syslog.html
 *
 * Write error messages to standard system files.
 *
 * On Ubuntu 15.10, running this a sudo generates a line like follows on /var/log/syslog:
 *
 *     Feb 10 20:17:30 pc-santilli syslog.out: syslog test: Success
 *
 * due to the special `%m`: errno message string.
 *
 * On Android, it logs to logcat:
 * https://stackoverflow.com/questions/5465941/what-is-the-log-api-to-call-from-an-android-jni-program/47133947#47133947
 *
 * TODO: %m generates a warning, due to our -std=c*, but I think it is a bug,
 * since %m is specified by POSIX, it must be due to the implementation detail
 * that printf is called internally by syslog.
 *
 * TODO: investigate if sudo is really needed.
 */

#include "common.h"

int main(void) {
    syslog(LOG_ERR | LOG_USER, "syslog test: %m\n");
    return EXIT_SUCCESS;
}
