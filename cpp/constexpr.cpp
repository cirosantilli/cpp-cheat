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

<http://stackoverflow.com/questions/3226211/why-is-it-ill-formed-to-have-multi-line-constexpr-functions>
*/
/*
constexpr int constexpr_func_multi_statement(int i) {
    int j;
    return i;
}
*/

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
        //{ constexpr int i = constexpr_func(std::time(NULL)); }
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

    {
        constexpr int i = 0;
        &i;
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
