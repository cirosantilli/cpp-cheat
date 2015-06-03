#include <stdio.h>

/*
Works as a GCC extension: this should fail without `extern`.
So common that even marked in the C99 "Common Extensions" Annex J.

http://stackoverflow.com/a/3692486/895245

GCC implements this in ELF with the `.common` section,
not with weak aliases (elf concept). TODO why?

With g++ it becomes a regular definition an linking fails.
*/
int commonInt;

/* ERROR already defined in a.c. Cannot redefine here. */
/*int commonInt = 0;*/

/*
Since there is no definition in `a.c`, this gets the default value of 0:
http://stackoverflow.com/questions/1597405/what-happens-to-a-declared-uninitialized-variable-in-c-does-it-have-a-value
*/
int commonUninitInt;

/*
Reference the one in main.

Unlike `commonInt`, if we remove the definition in a.c,
a link error would occur.
*/
extern int externInt;

/*
Warning: extern initialized.

It does not make much sense to add extern to a definition: only to a declaration.
*/
/*extern int externIntInt = 1;*/

void printMain() {
    commonInt++;
    externInt++;
    printf("commonInt = %d\n", commonInt);
    printf("externInt = %d\n", externInt);
}

void printA();

int main() {
    printA();
    printMain();
    printf("commonUninitInt = %d\n", commonUninitInt);
    return 0;
}
