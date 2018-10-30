/* https://en.cppreference.com/w/cpp/language/value_category
 * https://stackoverflow.com/questions/3601602/what-are-rvalues-lvalues-xvalues-glvalues-and-prvalues
 *
 * # xvalue
 *
 * # glvalue
 *
 * # prvalue
 *
 * In addition to the C99 rlvalues and values,
 * the C++11 standard defines new concepts:
 *
 * - xvalue
 * - glvalue
 * - prvalue
 *
 * http://stackoverflow.com/questions/3601602/what-are-rvalues-lvalues-xvalues-glvalues-and-prvalues
 *
 * This is probably a consequence of move semantics.
 */

#include "common.hpp"

#if __cplusplus >= 201103L
// https://stackoverflow.com/questions/36296425/how-to-determine-programmatically-if-an-expression-is-rvalue-or-lvalue-in-c
template <typename T>
constexpr bool is_lvalue(T&&) {
    return std::is_lvalue_reference<T>{};
}
#endif

int main() {
#if __cplusplus >= 201103L
    // TODO.
#endif
}
