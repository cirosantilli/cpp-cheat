// https://stackoverflow.com/questions/18118408/what-is-difference-between-quiet-nan-and-signaling-nan/55648118#55648118
//
// In C++ for signling_NaN.
//
// In GCC 8.2, sNaN is only done in -O0 and completely skipped in -O3.
// I'm not sure if there is a way to enforce it to happen.

#include <cassert>
#include <cfenv>
#include <cmath> // isnan
#include <csignal>
#include <cstring>
#include <iostream>
#include <limits> // std::numeric_limits
#include <unistd.h>

#pragma STDC FENV_ACCESS ON

void handler(int signum) {
    (void)signum;
    char message[] = "handler\n";
    write(STDOUT_FILENO, message, sizeof(message));
    feclearexcept(FE_ALL_EXCEPT);
}

int main() {
    if (
        std::numeric_limits<float>::has_signaling_NaN and
        std::numeric_limits<float>::has_signaling_NaN
    ) {
        float snan = std::numeric_limits<float>::signaling_NaN();
        float qnan = std::numeric_limits<float>::quiet_NaN();
        float f;

        // No exceptions.
        assert(std::fetestexcept(FE_ALL_EXCEPT) == 0);

        // Still no exceptions because qNaN.
        f = qnan + 1.0f;
        assert(std::isnan(f));
        if (std::fetestexcept(FE_ALL_EXCEPT) == FE_INVALID)
            std::cout << "FE_ALL_EXCEPT qnan + 1.0f" << std::endl;

        // Now we can get an exception because sNaN, but signals are disabled.
        f = snan + 1.0f;
        assert(std::isnan(f));
        if (std::fetestexcept(FE_ALL_EXCEPT) == FE_INVALID)
            std::cout << "FE_ALL_EXCEPT snan + 1.0f" << std::endl;
        feclearexcept(FE_ALL_EXCEPT);

#if 0
        // Handling like this leads to an infinite loop: the handler returns
        // to the instruction that generated the signal again!
        // The only way to get out is setjmp and longjmp:
        // https://stackoverflow.com/questions/39431879/c-handle-signal-sigfpe-and-continue-execution/39431923#39431923
        struct sigaction act;
        std::memset(&act, 0, sizeof(act));
        act.sa_handler = handler;
        act.sa_flags = SA_NODEFER | SA_NOMASK;
        sigaction(SIGFPE, &act, NULL);
#endif

        // And now we enable signals and blow up with SIGFPE! >:-)
        feenableexcept(FE_INVALID);
        f = qnan + 1.0f;
        std::cout << "feenableexcept qnan + 1.0f" << std::endl;
        f = snan + 1.0f;
        std::cout << "feenableexcept snan + 1.0f" << std::endl;
    }
}
