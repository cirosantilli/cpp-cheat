/* # time.h */

#include "common.h"

int main() {
    /*
    # time()

        A representation of absolute time.

        Returns a time_t type.

        The interpretation of the return is implementation defined,
        and therefore cannot be relied directly upon.

        Traditionally, implementations use the number of seconds since 1970.

    # time_t

        All that is required is that `time_t` be an arithmetic type, either integer or floating point.

        See printf for a discussion of how to print time_t.
    */
    {
        time_t t = time(NULL);
        printf("time(NULL) = %Lf\n", (long double)t);
    }

    /*
    # clock()

        Returns an implementation defined value:
        to get standard meaning out of it, you must use `CLOCKS_PER_SEC`.

        Usually represents the program virtual time in number of processor clock clicks

        Precision is quite limited, and if too few clicks pass, it may return 0.

        POSIX forces `CLOCKS_PER_SEC` to be 1 million as an XSI extension:
        http://pubs.opengroup.org/onlinepubs/009695399/basedefs/time.h.html
        and most modern systems use that value, giving a maximum of 1 microsecond precision.

        Consider `timespec_get` if you need greater precision, but for benchmarks you want user
        + system time only, not time, and there seems to be no ANSI C way:
        http://stackoverflow.com/questions/12392278/measure-time-in-linux-getrusage-vs-clock-gettime-vs-clock-vs-gettimeofday
        So this may be the best ANSI C benchmark method.

    # clock_t

        Type returned by `clock()`.

        `int` in glibc 2.21.

        Like `time_t`, all that is required is that `time_t` be an arithmetic type,
        either integer or floating point.

        See printf for a discussion of how to print a `clock_t`.
    */
    {
        /* On glibc 2.21, it is always an integer since `clock_t` is an integer. */
        clock_t t = clock();
        printf("clock() = %Lf\n", (long double)t);

        /*
        # CLOCKS_PER_SEC

            Divide a time delta by it to get elapsed time in seconds.

            In glibc 2.21, clock_t, so the division has integer precision only.
        */
        printf("CLOCKS_PER_SEC = %Lf\n", (long double)CLOCKS_PER_SEC);
    }

    /*
    # localtime

    # tm
    */
    {
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        printf("tm->tm_hour = %d\n", tm->tm_hour);
        printf("tm->tm_min = %d\n", tm->tm_min);
        printf("tm->tm_sec = %d\n", tm->tm_sec);
    }

    /*
    # Time to string

    - ctime
    - stftime
    */

    /*
    # strftime

        Convert time to a formatted string.

        The return value is stored in a statically allocated location:
        a second call to `localtime` may overwrite existing data.

        So make sure to copy if if you need to reuse it later.
    */
    {
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        char s[64];
        strftime(s, sizeof(s), "%c", tm);
        printf("strftime = %s\n", s);
    }

    /*
    # asctime

        `struct tm` to fixed format.

        POSIX 7 deprecates it in favor of `strftime`.
    */
    {
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        printf("asctime = %s\n", asctime(tm));
    }

    /*
    # ctime

        C99 says it is the same as:

            asctime(localtime(timer))
    */
    {
        time_t t = time(NULL);
        printf("ctime = %s\n", ctime(&t));
    }

    /*
    # milliseconds

    # microseconds

    # nanoseconds

        Added in C11 with timespec_get: http://stackoverflow.com/questions/361363/how-to-measure-time-in-milliseconds-using-ansi-c

        C++11 added one too: http://stackoverflow.com/questions/1487695/c-cross-platform-high-resolution-timer
    */

    return EXIT_SUCCESS;
}
