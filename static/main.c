#include <stdio.h>

void a();

int i = 0;
static int si = 0;

void m() {
    i++;
    si++;
    puts("m()");
    printf("i = %d\n", i);
    printf("si = %d\n", si);
    puts("");
}

int main() {
    m();
    m();
    a();
    a();
    return 0;
}
