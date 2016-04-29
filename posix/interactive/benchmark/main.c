#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#define _XOPEN_SOURCE 700
#include <sys/resource.h> /* getrusage */

typedef uint8_t type;

long double get_seconds(void) {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_utime.tv_sec + 1e-6 * usage.ru_utime.tv_usec +
           usage.ru_stime.tv_sec + 1e-6 * usage.ru_stime.tv_usec;
}

int main(int argc, char **argv) {
    long double seconds;
    uintmax_t i, nruns, size;
    type *array1;
    type *array2;

    if (argc > 1) {
        nruns = strtoumax(argv[1], NULL, 10);
    } else {
        nruns = 1000u;
    }
    if (argc > 2) {
        size = strtoumax(argv[2], NULL, 10);
    } else {
        size = 1000000u;
    }
    array1 = malloc(size * sizeof(type));
    array2 = malloc(size * sizeof(type));

    seconds = get_seconds();
    for (i = 0; i < nruns; ++i) {
        f1(array1, array2, size);
    }
    printf("%Lf\n", get_seconds() - seconds);
    seconds = get_seconds();
    for (i = 0; i < nruns; ++i) {
        f2(array1, array2, size);
    }
    printf("%Lf\n", get_seconds() - seconds);

    free(array1);
    free(array2);
    return EXIT_SUCCESS;
}
