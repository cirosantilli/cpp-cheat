/*
To break interactively in the infinite loop, enter Ctrl + C.

- http://stackoverflow.com/questions/8702658/gdb-how-do-i-pause-during-loop-execution
*/

#include <stdio.h>

static const int PERIOD = 100000000;

int main() {
    int i = 0;
    while (1) {
        i++;
        if (i % PERIOD == 0) {
            printf("%d\n", i / PERIOD);
            /*
            So that we can redirect to a file and observie it with `fail -f file`,
            and then attach GDB while it runs, without cluttering the GDB interface.
            http://superuser.com/questions/361474/how-to-redirect-output-from-an-infinite-loop-program
            */
            fflush(NULL);
        }
    }
}
