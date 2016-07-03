/*
# sleep

    Non busy sleep, that is, stop program execution for a given time,
    and let other programs run in the meantime.

    There is ANSI way of doing this.
*/

#include "common.h"

int main(void) {
    int i = 0;
    while (1) {
        printf("%d\n", i);
        sleep(1);
        i++;
    }
    return EXIT_SUCCESS;
}
