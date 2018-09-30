/*
https://stackoverflow.com/questions/27770896/how-to-debug-rare-deadlock

gdb -ex 'set confirm on' -ex=run -ex=quit --args ./maybe_crash.out
*/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    if (time(NULL) % 2) {
        raise(SIGINT);
    }
    puts("no crash");
    return EXIT_SUCCESS;
}
