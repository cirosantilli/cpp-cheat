/* Convert time to a formatted string.
 * https://stackoverflow.com/questions/1442116/how-to-get-the-date-and-time-values-in-a-c-program/30759067#30759067
 */

#include <assert.h>
#include <stdio.h>
#include <time.h>

int main(void) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char s[64];
    assert(strftime(s, sizeof(s), "%c", tm));
    printf("%s\n", s);
    return 0;
}
