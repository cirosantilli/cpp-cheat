/*
We can use memcmp and void* to simulate C++ templates like this.

Other possibilities:

- union of all possible types to use + enum
- macros

Biblography:

- http://stackoverflow.com/questions/10950828/simulation-of-templates-in-c
- http://stackoverflow.com/questions/5551427/generic-data-type-in-c-void
- http://stackoverflow.com/questions/3039513/type-safe-generic-data-structures-in-plain-old-c
*/

#include "common.h"

typedef struct Stack Stack;
struct Stack {
    void *data;
    size_t nelems;
    size_t elem_size;
    size_t nelems_capacity;
};

void Stack_init(Stack *stack, size_t elem_size, size_t nelems_capacity) {
    stack->nelems = 0;
    stack->elem_size = elem_size;
    stack->nelems_capacity = nelems_capacity;
    stack->data = malloc(nelems_capacity * elem_size);
}

void Stack_deinit(Stack *stack) {
    free(stack->data);
}


int Stack_push(Stack *stack, void *data) {
    Stack *buffer;
    if (stack->nelems == stack->nelems_capacity) {
        stack->nelems_capacity *= 2;
        buffer = realloc(stack->data, stack->nelems_capacity);
        if (buffer == NULL)
            return 1;
        stack->data = buffer;
    }
    stack->nelems++;
    memcpy(&((uint8_t *)(stack->data))[stack->nelems * stack->elem_size], data, stack->elem_size);
    return 0;
}

int Stack_pop(Stack *stack, void *elem) {
    if (stack->nelems == 0)
        return 1;
    stack->nelems--;
    memcpy(elem, &((uint8_t *)(stack->data))[stack->nelems * stack->elem_size], stack->elem_size);
    return 0;
}

int main(void) {
    Stack *s;
    typedef int t;
    uint8_t data[sizeof(t)];
    /* TODO segfaulting. This was not properly testd. */
    /*Stack_init(s, sizeof(t), 2);*/
    /*Stack_push(s, 0);*/
    return EXIT_SUCCESS;
}
