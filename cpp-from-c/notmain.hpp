#ifndef NOTMAIN_HPP
#define NOTMAIN_HPP

#ifdef __cplusplus
// C cannot see these overloaded prototypes, or else it would get confused.
int f(int i);
int f(float i);
extern "C" {
#endif
int f_int(int i);
int f_float(float i);
#ifdef __cplusplus
}
#endif

#endif
