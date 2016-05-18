#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <fenv.h>
#include <float.h>
#include <inttypes.h> /* PRIxPTR,  */
#include <iso646.h>
#include <limits.h> /* *_MAX, *_MIN for integer types */
#include <locale.h>
#include <setjmp.h> /* setjmp, longjmp */
#include <signal.h>
#include <stdbool.h> /* false, true */
#include <stdarg.h> /* ..., va_list, va_start, va_arg, va_end */
#include <stddef.h> /* offsetof, ptrdiff_t, size_t, type_t */
#include <stdlib.h> /* EXIT_SUCCESS, EXIT_FAILURE, malloc, rand, srand */
#include <stdio.h> /* printf, puts */
#include <string.h> /* sprintf, strlen, strcpy, memset, memcmp */
#include <math.h>
#include <time.h> /* time() */
#include <wchar.h>
#if __STDC_VERSION__ >= 199901L
  /* Not yet implemented in GCC 5.2. */
/*#  include <threads.h>*/
# ifndef __STDC_NO_COMPLEX__
#  include <complex.h>
# endif
# if __STDC_VERSION__ >= 201112L
#  include <stdnoreturn.h>
# endif
#endif

#define PRIxPTR_WIDTH ((int)(sizeof(void*)*2))

#define GCC_PUSH GCC diagnostic push
/* TODO not working. */
#define GCC_IGNORE(x) GCC diagnostic ignored x
#define GCC_POP GCC diagnostic pop
