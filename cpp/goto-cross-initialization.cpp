/*
Jump crosses initialization of ...
http://stackoverflow.com/questions/5685471/error-jump-to-case-label

Same with switch cases.
*/

#include "common.hpp"

int main() {
    goto after
    ;
    // ERROR
    //int i = 0;
after:
    ;
}
