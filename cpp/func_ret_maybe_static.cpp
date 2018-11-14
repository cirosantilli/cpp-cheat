// https://stackoverflow.com/questions/53304666/how-to-make-a-function-that-can-return-either-a-static-or-automatic-storage-obje
// https://stackoverflow.com/questions/24344479/how-can-a-function-in-c-return-either-a-value-or-a-reference-with-minimal-copy

#include <cassert>
#include <iostream>
#include <memory>

struct C {
    int i;
    static int count;
    C(int i) : i(i) {
        std::cout << "constr" << std::endl;
        count++;
    }
    C(const C& c) : C(c.i) {
        std::cout << "copy" << std::endl;
    }
    ~C() {
        std::cout << "destr" << std::endl;
        count--;
    }
};
int C::count = 0;

std::shared_ptr<C> func_reg_maybe_static(int i) {
    static auto static_obj = std::make_shared<C>(0);
    if (i == 0) {
        return static_obj;
    } else {
        return std::make_shared<C>(i);
    }
}

int main() {
    assert(C::count == 0);

    {
        auto c(func_reg_maybe_static(0));
        assert(c->i == 0);
        assert(C::count == 1);
    }
    assert(C::count == 1);

    {
        auto c(func_reg_maybe_static(0));
        assert(c->i == 0);
        assert(C::count == 1);
    }
    assert(C::count == 1);

    {
        auto c(func_reg_maybe_static(1));
        assert(c->i == 1);
        assert(C::count == 2);
    }
    assert(C::count == 1);

    {
        auto c(func_reg_maybe_static(2));
        assert(c->i == 2);
        assert(C::count == 2);
    }
    assert(C::count == 1);
}
