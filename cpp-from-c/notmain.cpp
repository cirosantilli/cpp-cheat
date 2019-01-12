#include "notmain.hpp"

int f(int i) {
    return i + 1;
}

int f(float i) {
    return i + 2;
}

int f_int(int i) {
    return f(i);
}

int f_float(float i) {
    return f(i);
}
