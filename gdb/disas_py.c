#include <stdio.h>
#include <time.h>

int main() {
    int i;
    i  = time(NULL);
    /* This should generate an inner block. */
    {
        int i;
        i = time(NULL);
        printf("%d\n", i);
    }
    printf("%d\n", i);
    return 0;
}
