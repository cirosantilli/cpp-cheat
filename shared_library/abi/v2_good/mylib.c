#include <stdlib.h>

#include "mylib.h"

mylib_mystruct* mylib_init(int old_field) {
    mylib_mystruct *myobject;
    myobject = malloc(sizeof(mylib_mystruct));
    myobject->old_field = old_field;
    myobject->new_field = 2;
    return myobject;
}
