#include <stdio.h>

const static int PERIOD = 100000000;

int main() {
    int i = 0;
    while (1) {
        i++;
        if (i % PERIOD == 0)
            printf("%d\n", i / PERIOD);
    }
}
