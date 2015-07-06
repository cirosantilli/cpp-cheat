#ifndef C_H
#define C_H

#ifdef __cplusplus
// This is required otherwise he C++ includer will look
// for the undefined mangled name.
extern "C" {
#endif
    int f();
#ifdef __cplusplus
}
#endif

#endif
