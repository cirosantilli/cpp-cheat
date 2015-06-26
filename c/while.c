/* # while */

#include "common.h"

int main() {
    /* Basic example. */
    {
        int i = 0;
        int is[] = { 0, 1, 2 };
        while (i < 3) {
            assert(i == is[i]);
            i++;
        }
        assert(i == 3);
    }

    /* # do-while */
    {
        int i = 0;
        int i2;
        int is[] = { 0, 1, 2 };
        do {
            i2 = 2*i*i + 3*i + (i % 2);
            assert(i == is[i]);
            i++;
        } while (i2 < 7);
        /* Don't forget the ';'. */

        /*
        Application Loop must execute at least once to know if it will continue.

        Without do-while, you would have to either:

        -   `int i2 = 2*i*i + 3*i + (i % 2);`

            So you have to type this huge expression twice!

        -   write a function that does:

                2*i*i + 3*i + (i % 2);

            This function is almost useless (used only twice)
            adding needless boilerplate to your code.

        both of which are not very attractive alternatives.
        */
    }

    return EXIT_SUCCESS;
}
