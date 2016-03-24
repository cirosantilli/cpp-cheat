#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static long get_nanos() {
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return (long)ts.tv_sec * 1000000000L + ts.tv_nsec;
}

int main() {
    long nanos;
    long last_nanos;
    long start;
    nanos = get_nanos();
    last_nanos = nanos;
    start = nanos;
    while (1) {
        nanos = get_nanos();
        if (nanos - last_nanos > 1000000L) {
            printf("current nanos: %ld\n", nanos - start);
            last_nanos = nanos;
        }
    }
    return EXIT_SUCCESS;
}
