#include <cassert>

#include "notmain.hpp"

int main() {
    // Both files see the same memory address.
    assert(&notmain_i == notmain_func());
    assert(notmain_i == 42);
}
