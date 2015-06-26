/*
# setjmp.h

    Jumps without scope restrictions of goto labels.

    # setjmp

        Saves register states, including instruction and pointer registers.

        Return value:

        - 0 if did not return from longjmp
        - != 0 if just returned from a lonjmp

        Application: error handling a la exception. Return val encodes the exception type.

    # longjmp

        Restores register states.

    # longjmp and signals

        If you longjmp from a signal handler you can recatch the signal afterwards.
*/

#include "common.h"

int setjmp_func(int jmp, jmp_buf env_buf) {
    if (jmp)
        longjmp(env_buf, 1);
    else
        return 1;
}

int main() {
    jmp_buf env_buffer;
    int val;

    val = setjmp(env_buffer);
    printf("setjmp = %i\n", val);
    if (val != 0) {
        /* Returned from longjmp. */
        /* Val encodes the error code. */
    } else {

        /* This is evaulated normally. */
        assert(setjmp_func(0, env_buffer) == 1);

        /* This assert is never evaluated. */
        assert(setjmp_func(1, env_buffer) * 0 == 1);
    }

    return EXIT_SUCCESS;
}
