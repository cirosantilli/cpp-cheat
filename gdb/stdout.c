/*
http://stackoverflow.com/questions/8235436/how-can-i-monitor-whats-being-put-into-the-standard-out-buffer-and-break-when-a
http://stackoverflow.com/questions/1538463/how-can-i-put-a-breakpoint-on-something-is-printed-to-the-terminal-in-gdb
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
    puts("a");
    puts("b");
    return EXIT_SUCCESS;
}
