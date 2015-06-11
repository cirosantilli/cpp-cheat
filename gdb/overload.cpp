/*
    b f

will add breakpoints to both overloads.

To differentiate between them, use:

    b f(int)
    b f(float)
*/

#include <iostream>

void f(int i) {
    std::cout << "int" << std::endl;
}

void f(float f) {
    std::cout << "float" << std::endl;
}

int main() {
    f(1);
    f(1.0f);
}
