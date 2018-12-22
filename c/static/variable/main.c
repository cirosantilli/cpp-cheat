#include <assert.h>
#include <stdlib.h>

#include "notmain.h"

int main_i = 0;
static int static_i = 10;

void main_func() {
    main_i++;
    static_i++;
}

int main(void) {
    int notmain_main_i, notmain_static_i, notmain_static_i_function;

    /* main_func */
    {
        assert(main_i == 0);
        assert(static_i == 10);

        main_func();
        assert(main_i == 1);
        assert(static_i == 11);

        main_func();
        assert(main_i == 2);
        assert(static_i == 12);
    }

    /* notmain_func */
    {
        notmain_func(
            &notmain_main_i,
            &notmain_static_i,
            &notmain_static_i_function
        );
        assert(main_i == 3);
        assert(static_i == 12);
        assert(notmain_main_i == main_i);
        assert(notmain_static_i == 21);
        assert(notmain_static_i_function == 31);

        notmain_func(
            &notmain_main_i,
            &notmain_static_i,
            &notmain_static_i_function
        );
        assert(main_i == 4);
        assert(static_i == 12);
        assert(notmain_main_i == main_i);
        assert(notmain_static_i == 22);
        assert(notmain_static_i_function == 32);
    }

    return EXIT_SUCCESS;
}
