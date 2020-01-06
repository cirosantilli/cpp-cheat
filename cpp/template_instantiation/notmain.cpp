#include "notmain.hpp"

template<class T>
T MyClass<T>::f(T t) { return t + 1; }

// Only int is instantiated.
template class MyClass<int>;
