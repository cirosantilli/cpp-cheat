/*
# syslog

    Write error messages to standard system files.

    Interface:

        void syslog(int priority, const char *message, arguments...);

    Error levels:

    - `LOG_EMERG`:   Description.
    - `LOG_ALERT`:   Emergency situation.
    - `LOG_CRIT`:    High-priority problem, such as database corruption.
    - `LOG_ERR`:     Critical error, such as hardware failure.
    - `LOG_WARNING`: Errors.
    - `LOG_NOTICE`:  Warning.
    - `LOG_INFO`:    Special conditions requiring attention.
    - `LOG_DEBUG`:   Informational messages.

    Error source:

    - `LOG_USER`: a user space application
    - `LOG_LOCAL[0-7]`: left for admins to specify

    Message: accepts format strings similar to printf with extensions.

    - %m: errno message string

    On Ubuntu 15.10, generates a line like follows on /var/log/syslog:

        Feb 10 20:17:30 pc-santilli syslog.out: syslog test: Success
*/

#include "common.h"

int main() {
    syslog(LOG_ERR | LOG_USER, "syslog test: %m\n");
    return EXIT_SUCCESS;
}
