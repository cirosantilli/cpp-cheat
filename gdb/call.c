/*
- https://stackoverflow.com/questions/1354731/how-to-evaluate-functions-in-gdb
- https://jvns.ca/blog/2018/01/04/how-does-gdb-call-functions/
*/

#include <stdio.h>

/* Memory side effects are not reverted. */
int global = 0;

int f(int x) {
    printf("%d\n", x);
    global++;
    return x + 1;
}

int main(void) {
    /* Try:
     * (gdb) call f(1)
     * (gdb) p global
     * (gdb) call f(2)
     * (gdb) p global
     * */
    printf("%d\n", f(1));
    return 0;
}
