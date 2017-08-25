#include <stdio.h>

typedef struct {
    int i;
    float f;
} S;

S s = {1, 1.1};

int main() {
    printf("%d %f\n", s.i, s.f);
    s.i = 2;
    s.f = 2.2;
    s.i = 3;
    s.f = 3.3;
    return 0;
}
