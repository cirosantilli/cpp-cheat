/*
# builtin_prefetch

# __builtin_prefetch

    Pulls data into cache shortly before it is needed.

    Signature:

        void __builtin_prefetch(const void *addr, ...);

    - addr: The address of the data
    - rw:

        Second optional argument.

        Indicates whether the data is being pulled in for Read or preparing for a Write operation

        - 0 = r (default)
        - 1 = w

    - locality:

        Degree of temporal locality of variable.

        Third optional argument.

        Integer in [0,3] range.

        - 0 means no temporal locality, so it can be removed from cache immediately after use.
        - 3 means very high temporal locality, should stay on the cache afterwards.

        3 is the default value.

    I could not manage to make GCC generate different assembly output in the two cases.
*/

#include "common.h"

/* Do some random operations to try and get the cache dirty. */
void get_cache_dirty() {
    int i;
    int is[1024];
    for (i = 0; i < 1024; i++)
        is[i] = 1;
    assert(is[0] == 1);
}

int main() {
    int j = 1;

    get_cache_dirty();
    __builtin_prefetch(&j, 0, 0);
    assert(j == 1);

    get_cache_dirty();
    assert(j == 1);

    return EXIT_SUCCESS;
}
