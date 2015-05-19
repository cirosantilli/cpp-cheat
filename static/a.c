#include <stdio.h>

/* Link time error: already defined in main. */
/*int i = 0;*/

/* OK: only declared, not defined. Will use the one in main. */
int i;

/* OK: only visible to this file. */
static int si = 0;

void a() {
    i++;
    si++;
    puts("a()");
    printf("i = %d\n", i);
    printf("si = %d\n", si);
    puts("");
}
