#include <iostream>

int main(void) {
#ifdef __cplusplus
    std::cout << __cplusplus << std::endl;
#endif
#ifdef __STRICT_ANSI__
    std::cout << "__STRICT_ANSI__" << std::endl;
#endif
    return 0;
}
