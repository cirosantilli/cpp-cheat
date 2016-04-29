/*
C11 for clock_gettime
http://stackoverflow.com/questions/361363/how-to-measure-time-in-milliseconds-using-ansi-c/36095407#36095407

Vs clock: http://stackoverflow.com/questions/12392278/measure-time-in-linux-getrusage-vs-clock-gettime-vs-clock-vs-gettimeofday
All we know about the clock output is that dividing it by 
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
We use double because time_t can be either floating point or integer.
POSIX guarantees that it is an integer, we could use uintmax_t then.
*/
static long double get_nanos(void) {
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return ts.tv_sec * 1e9 + ts.tv_nsec;
}

int main(void) {
    long double last_nanos;
    long double nanos;
    long double start;
    nanos = get_nanos();
    last_nanos = nanos;
    start = nanos;
    while (1) {
        nanos = get_nanos();
        if (nanos - last_nanos > 1e7) {
            printf("%Lf\n", nanos - start);
            last_nanos = nanos;
        }
    }
    return EXIT_SUCCESS;
}
