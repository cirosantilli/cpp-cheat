#include <stdio.h>

/* Link time error: already defined in main. */
/*int i = 0;*/

/*
OK: only declared, not defined. Will be marked as common,
and default to the one in main.
*/
extern int i;

/* OK: only visible to this file. */
static int si = 0;

void a() {
    static int sil = 0;
    i++;
    si++;
    puts("a()");
    printf("i = %d\n", i);
    printf("si = %d\n", si);
    puts("");
}
