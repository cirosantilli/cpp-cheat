#ifndef MYLIB_H
#define MYLIB_H

typedef struct {
    int old_field;
    int new_field;
} mylib_mystruct;

mylib_mystruct* mylib_init(int old_field);

#endif
