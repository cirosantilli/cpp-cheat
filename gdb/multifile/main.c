#include <assert.h>

extern int a_i, d_a_i, d_b_i, e_a_i;
int a_f(), d_a_f(), e_a_f();
int a_g(), d_a_g(), e_a_g();
int        d_b_f();
int        d_b_g();

int main_a = 1;
int main_f() { return 1; }
int main_g() { return 1; }

int main() {
    assert(main_a == 1);
    assert(main_f() == 1);
    assert(main_g() == 1);
    assert(d_a_i == 1);
    assert(d_a_f() == 1);
    assert(d_a_g() == 1);
    assert(d_b_i == 1);
    assert(d_b_f() == 1);
    assert(d_b_g() == 1);
    assert(e_a_i == 1);
    assert(e_a_f() == 1);
    assert(e_a_g() == 1);
    return 0;
}
