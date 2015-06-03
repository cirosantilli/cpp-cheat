#include <assert.h>
#include <ctype.h> /* isspace, isdigit, ispunct, tolower, toupper */
#include <errno.h>
#include <fenv.h>
#include <float.h>
#include <inttypes.h> /* PRIxPTR */
#include <limits.h> /* *_MAX, *_MIN for integer types */
#include <locale.h>
#include <setjmp.h> /* setjmp, longjmp */
#include <signal.h>
#include <stdarg.h> /* ..., va_list, va_start, va_arg, va_end */
#include <stddef.h> /* offsetof, type_t */
#include <stdlib.h> /* malloc, EXIT_SUCCESS, EXIT_FAILURE: */
#include <stdio.h> /* printf, puts */
#include <string.h> /* sprintf, strlen, strcpy, memset, memcmp */
#include <math.h>
#include <time.h> /* time() */
#if __STDC_VERSION__ >= 199901L
 /* Not yet implemented in GCC 4.8. */
 /*#include <thread.h>*/
# if __STDC_VERSION__ >= 201112L
#  include <stdnoreturn.h>
# endif
#endif

#define PRIxPTR_WIDTH ((int)(sizeof(void*)*2))
