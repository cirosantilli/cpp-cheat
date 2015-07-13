#include <stdio.h>
#include <time.h>

int main() {
    int i;
    if (time(NULL) % 2) {
        i = 0;
    } else {
        puts("1");
        return 1;
    }
    printf("%d", i);
    return 0;
}
