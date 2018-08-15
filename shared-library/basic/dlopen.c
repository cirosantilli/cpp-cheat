#define _XOPEN_SOURCE 700
#include <assert.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

#include "a.h"
#include "b.h"

int main() {
    void *handle;
    int (*a)(void);
    int (*b)(void);
    char *error;

    handle = dlopen("libcirosantilli_ab.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }
    dlerror();
    a = (int (*)(void)) dlsym(handle, "a");
    b = (int (*)(void)) dlsym(handle, "b");
    error = dlerror();
    if (error != NULL) {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }
    assert(a() == 1);
    assert(b() == 2);
    dlclose(handle);
    return EXIT_SUCCESS;
}
