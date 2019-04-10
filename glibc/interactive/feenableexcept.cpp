// In C++ for signling_NaN.

#include <cassert>
#include <cfenv>
#include <cmath> // isnan
#include <csignal>
#include <cstring>
#include <iostream>
#include <limits> // std::numeric_limits
#include <unistd.h>

void handler(int signum) {
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
        assert(std::fetestexcept(FE_ALL_EXCEPT) == 0);

        // Now we get an exception because sNaN, but signals are disabled.
        f = snan + 1.0f;
        assert(std::isnan(f));
        assert(std::fetestexcept(FE_ALL_EXCEPT) == FE_INVALID);
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
        std::cout << "quiet" << std::endl;
        f = snan + 1.0f;
        // Never reached.
        std::cout << "signaling" << std::endl;
    }
}
