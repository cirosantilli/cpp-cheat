#include <assert.h>
#include <stdlib.h>

int f_1_2(void);
int f_2_1(void);

int main(void) {
    assert(f_1_2() + f_2_1() == 5);
    return EXIT_SUCCESS;
}
