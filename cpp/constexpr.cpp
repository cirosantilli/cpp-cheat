/*
# constexpr

    C++11 keyword.

    `const` variables can either be compile time constants or not.

    The compiler is able to decide that at compile time, but it may be hard for human
    readers to predict if a given variable is a constexpr of not.

    Using the constexpr keyword however makes the compiler ensure that the variables are constant expressions,
    so that the compile time constantness is more explicit.

    Two uses:

    -   variables

        Means that the value of an expression is known at compile time.

    -   functions

        The value returned by constexpr functions is known to be a compile time constant.

        The compiler enforces this by inspecting the function.
*/

#include "common.hpp"

#if __cplusplus >= 201103L
int not_constexpr_func() {
    return 1;
}

constexpr int constexpr_func(int i) {
    return i;
}

/*
C++11 specifies that the body of a constexrp function must contain a single return statement.

Otherwise, it would be too much work for the compiler to do.

http://stackoverflow.com/questions/3226211/why-is-it-ill-formed-to-have-multi-line-constexpr-functions

C++ 14 lifts it.

constexpr functions have several restrictions: in broad terms, they cannot have side effects:
https://stackoverflow.com/questions/5112305/why-not-to-declare-a-function-constexpr
which is cool, feels like functional pure functions.
*/
#if __cplusplus >= 201402L
constexpr int constexpr_func_multi_statement(int i) {
    // ERROR: cannot have uninitialized vars.
    //int j;
    // ERROR: cannot call non constexpr functions
    //std::time(NULL);
    return i;
}
#endif

class MyClass {
    public:
        MyClass() : i(1) {}
        constexpr MyClass(int i) : i(i) {}
        // ERROR: Nah, no overload.
        //MyClass(int i) : i(i) {}
        int i;
        static int member;
        constexpr int f(int j) const { return this->i + j; }
        constexpr int noThis(int j) const { return j + 1; }
        int nonConst() const { return std::time(NULL); }
        // ERROR: constexpr data must be static, or this wouldn't make much sense / be useful, right?
        //constexpr int nonStaticConstexpr;
};

constexpr int ConstexprFactorial(int n) {
    return (n == 1) ? 1 : n * ConstexprFactorial(n - 1);
}

/*
ERROR: the compiler ensures that the function return is constexpr,
so this does not compile.
*/
/*
int constexpr constexpr_func_bad(){
    return std::time();
}
*/
#endif

int main() {
#if __cplusplus >= 201103L
    // OK: built-in operators that take constexprs return a constexpr
    {
        constexpr int i = 1 + 1;
    }

    // OK: it is a constexpr
    {
        constexpr int i = 0;
        constexpr int i2 = i;
    }

    // OK: the compiler sees that a const initialized by a constexpr is also a constexpr.
    {
        const int i = 0;
        constexpr int i2 = i;
    }

    // ERROR: for non built-in operators, only constexpr functions can be used.
    {
        //constexpr int i = not_constexpr_func();
    }

    // constexpr functions only work if all their arguments are constexprs.
    {
        { constexpr int i = constexpr_func(1); }
        // ERROR
        //{ constexpr int i = constexpr_func(std::time(NULL)); }
    }

    // constexpr object
    {
        constexpr MyClass myClass(1);
        MyClass myClassNonConst;

        // ERROR: not using constexpr constructor on constexpr object.
        //{ constexpr MyClass myClass; }

        // Fine with non constexpr constructor.

        // Now we can use members further constexpr chains.
        { constexpr int i = myClass.i; }
        // ERROR
        //{ constexpr int i = myClassNonconst.i; }

        // Methods that don't use this don't need the constexpr object.
        { constexpr int i = myClassNonConst.noThis(1); }
        // But if the method uses this, then it needs.
        { constexpr int i = myClass.f(1); }
        // ERROR
        //{ constexpr int i = myClassNonConst.f(1); }

        // Can still call non constexpr methods of the const object.
        { int i = myClass.nonConst(); }
        // ERROR But not initialize constexpre expressions with them.
        //{ constexpr int i = myClass.nonConst(); }
    }

    // Recursive functions can be constexpr, as long as they fit into one line.
    {
        constexpr int i = ConstexprFactorial(3);
        assert(i == 6);
    }

    // ERROR: the compiler sees that this is not a constexpr.
    // Avoid relying on this execept for legacy code: always initialize a constexpr from constexprs!
    {
        const int i = std::time(NULL);
        //constexpr int i2 = i + 1;
    }

    // ERROR: it is not a constexpr
    {
        int i = 0;
        //i = std::time(NULL);
        // We could change i at any time!
        //constexpr int i2 = i + 1;
    }

    // ERROR: constexprs cannot be modified after initialization
    {
        constexpr int i = 0;
        //i = 1;
    }

    // constexpr do have addresses. But likely they will inlined when addresses are never taken.
    {
        constexpr int i = 1;
        constexpr int j = 2;
        const int *ip = &i;
        const int *jp = &j;
        assert(*ip == 1);
        assert(*jp == 2);
        assert(ip != jp);
    }

    // WARN: unitialized constexpr
    {
        //constexpr int i;
    }

    /*
    cannot have constexpr to complex types

    TODO rationale
    */
    {
        //constexpr std::string s = "abc";
    }
#endif
}
