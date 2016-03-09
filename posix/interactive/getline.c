/*
# getline

    Best POSIX way to read lines of unknown lengths.

    Could be implemented in ANSI C:
    http://stackoverflow.com/questions/314401/how-to-read-a-line-from-the-console-in-c

    POSIX has a clear file example at:
    http://pubs.opengroup.org/onlinepubs/9699919799/functions/getdelim.html

    Allocates memory. Can then reuse the line pointer multiple times for a loop.

    The second parameter exists only to say how big the buffer currently is:
    it can be larger than the actual line width.

    And it must be updated if a longer line comes.
*/

#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char *line = NULL;
    size_t len = 0;
    ssize_t read = 0;
    while (read != -1) {
        puts("enter a line");
        read = getline(&line, &len, stdin);
        printf("line = %s", line);
        printf("line length = %zu\n", read);
        puts("");
    }
    free(line);
    return 0;
}
