#include <assert.h>
#include <stdlib.h>

#include "mylib.h"

int main(void) {
    mylib_mystruct *myobject = mylib_init(1);
    assert(myobject->old_field == 1);
    free(myobject);
    return EXIT_SUCCESS;
}
