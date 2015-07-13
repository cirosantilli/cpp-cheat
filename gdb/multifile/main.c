#include <assert.h>

int i;
extern int a;

int main() {
    assert(a == 1);
    return 0;
}
