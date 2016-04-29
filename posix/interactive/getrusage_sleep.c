/*
- getrusage, it really measures used process scheduled time, sleeps / blocks are ignored.
- CLOCK_PROCESS_CPUTIME_ID: TODO what does it measure? why not 0?
*/

#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <sys/resource.h> /* getrusage */
#include <unistd.h> /* sleep */

long double get_seconds_getrusage(void) {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_utime.tv_sec + 1e-6 * usage.ru_utime.tv_usec +
           usage.ru_stime.tv_sec + 1e-6 * usage.ru_stime.tv_usec;
}

long double get_seconds_clock_gettime_process_cpu(void) {
    struct timespec ts;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts);
    return ts.tv_sec + 1e-9 * ts.tv_nsec;
}

int main(void) {
    long double seconds;

    seconds = get_seconds_getrusage();
    sleep(1);
    printf("%.9Lf\n", get_seconds_getrusage() - seconds);

    seconds = get_seconds_clock_gettime_process_cpu();
    sleep(1);
    printf("%.9Lf\n", get_seconds_clock_gettime_process_cpu() - seconds);

    return EXIT_SUCCESS;
}
