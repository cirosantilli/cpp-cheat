/*
# Parameter without name

    In C, illegal on function definition, only for declaration.

    In C++ it became legal, likely because it is useful
    when overriding does not use the parameter.

    http://stackoverflow.com/questions/2319663/why-does-c-code-missing-a-formal-argument-name-in-a-function-definition-compil
*/

#include "common.hpp"

int f(int) {
    return 1;
}

int g(int = 2) {
    return 1;
}

int main() {
    assert(f(0) == 1);

    /* It is also possible to give them default values. */
    assert(g(0) == 1);
    assert(g() == 1);
}
