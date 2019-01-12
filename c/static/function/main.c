#include <assert.h>
#include <stdlib.h>

/* OK: only declared, not defined. Will use the one in notmain. */
int notmain_add(void);

/* OK: only visible to this file. */
static int static_func(void) {
    return 0x10;
}

int main_func(void) {
    return 0x1;
}

int main_add(void) {
    return main_func() + static_func();
}

int main(void) {
    assert(main_add() == 0x011);
    assert(notmain_add() == 0x101);
    return EXIT_SUCCESS;
}
