#include <stdio.h>

#define _XOPEN_SOURCE 700
#include <sys/types.h> /* pid_t */
#include <unistd.h> /* fork */

int main() {
    pid_t pid = fork();
    if (pid == 0) {
        puts("child");
    } else {
        puts("parent");
    }
    return 0;
}
