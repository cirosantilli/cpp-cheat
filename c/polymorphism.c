/*
http://stackoverflow.com/questions/524033/how-can-i-simulate-oo-style-polymorphism-in-c
*/

#include "common.h"

typedef struct {
    int (*f)(int i, int j);
    int (*g)(int i, int j);
} base;

int f1(int i, int j) {
    return i + j;
}

int f2(int i, int j) {
    return i + j + 1;
}

int g1(int i, int j) {
    return i * j;
}

int g2(int i, int j) {
    return i * j * 2;
}

void init1(base *b) {
    b->f = f1;
    b->g = g1;
}

void init2(base *b) {
    b->f = f2;
    b->g = g2;
}

int main(void) {
    base bases[2];
    init1(&bases[0]);
    init2(&bases[1]);
    assert(bases[0].f(2, 3) == 5);
    assert(bases[0].g(2, 3) == 6);
    assert(bases[1].f(2, 3) == 6);
    assert(bases[1].g(2, 3) == 12);
    return EXIT_SUCCESS;
}
