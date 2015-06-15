#include <stdio.h>

typedef struct {
    int i;
    float f;
} S;

S s = {1, 1.1};

int main() {
    printf("%d %f\n", s.i, s.f);
    return 0;
}
