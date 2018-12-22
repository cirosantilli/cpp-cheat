#include "notmain.hpp"

const int notmain_i = 42;

const int* notmain_func() {
    return &notmain_i;
}
