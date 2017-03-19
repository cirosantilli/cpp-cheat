/*
# random

# srand

    Seed the random number generator.

    It is very common to seed with `time(NULL)` for simple applications,
    but this is a cryptographic disaster as it is very easy to try out all possible initial seconds.

# rand

    Get a uniformly random `int` between 0 and RAND_MAX.

    For cryptographic applications, use a library:
    http://crypto.stackexchange.com/questions/15662/how-vulnerable-is-the-c-rand-in-public-cryptography-protocols

    On Linux, `/dev/random` is the way to go.

    Intel introduced a RdRand in 2011, but as of 2015 it is not widely used,
    and at some point was used as part of the entropy of `/dev/random`.
*/

#include "common.h"

/*
Make `s` into a random string of length len (excluding the null character),
with alphanumeric characters.

`s` must be at least `len + 1` wide.
*/
void random_string(char * const s, const size_t len) {
    size_t i;
    static const char c[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    for (i = 0; i < len; ++i)
        s[i] = c[rand() % (sizeof(c) - 1)];
    s[len] = 0;
}

void random_array(char * const arr, const size_t len) {
    size_t i;
    for (i = 0; i < len; ++i)
        arr[i] = rand() % SCHAR_MAX;
}

int main(void) {
    srand(time(NULL));

    /*
    Integer between 0 and RAND_MAX:
    */
    {
        printf("rand() = %d\n", rand());
        printf("rand() = %d\n", rand());
        assert(0 <= rand());
        assert(rand() <= RAND_MAX);
    }

    /*
    # RAND_MAX

        At least a signed 16 bit integer.
    */
    {
        printf("RAND_MAX = %jx\n", (uintmax_t)RAND_MAX);
        assert(RAND_MAX >= ((1 << 15) - 1));
    }

    /* int between 0 and 99: */
    {
        int i = rand() % 99;
    }

    /* float between 0 and 1: */
    {
        float f = rand() / (float)RAND_MAX;
    }

    /* float in given range. */
    {
        float min = 1.0f;
        float max = 3.0f;
        float res = (max - min) * ((float)rand() / RAND_MAX) + min;
        printf("float in range = %f\n", res);
    }

    /*
    # random string

        No built-in way.

        http://stackoverflow.com/questions/440133/how-do-i-create-a-random-alpha-numeric-string-in-c
    */
    {
        char s[16];
        random_string(s, 15);
        printf("random_string = %s\n", s);
        random_string(s, 15);
        printf("random_string = %s\n", s);
    }

    /*
    # random array
    */
    {
        char s[16];
        random_array(s, 16);
    }

    return EXIT_SUCCESS;
}
