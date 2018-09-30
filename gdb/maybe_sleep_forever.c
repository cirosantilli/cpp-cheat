/*
https://stackoverflow.com/questions/50066342/how-to-get-a-notification-if-a-given-process-runs-for-longer-than-a-specified-ti
*/

#define _XOPEN_SOURCE 700
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(void) {
    if (time(NULL) % 2) {
        sleep(3);
    } else {
        while (1) {
            sleep(0x7FFFFFFF);
        }
    }
    return EXIT_SUCCESS;
}
