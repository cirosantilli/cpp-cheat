#ifndef CPP_H
#define CPP_H

#ifdef __cplusplus
// This is required otherwise C++ will compile to mangled names,
// and the C includer will not find them.
extern "C" {
#endif
    int f();
#ifdef __cplusplus
}
#endif

#endif
