/*
# wchar.h

    Wide Character.

    For Unicode character and string operations.

# Unicode

    Use wchar.

*/

#include "common.h"

int main() {
    char cs[] = "汉语";
    printf("%s\n", cs);

    /* BAD: only changes first byte you get trash all over: */
    /*cs[0] = 'a';*/
    /*printf("%s\n",cs);*/

    /* WARN */
    /*cs[0] = '英';*/

    /* You *need* setlocale to print correctly: */
    setlocale(LC_CTYPE, "");

    wchar_t wcs[] = L"汉语";

    printf("%ls\n", wcs);

    assert(wcs[0] = L'汉');
    wcs[0] = L'英';
    printf("%ls\n", wcs);

    wcs[0] = L'a';
    printf("%ls\n", wcs);

    /* ERROR: non wide init */
    /*wchar_t wideString2[] = "asdf";*/

    return EXIT_SUCCESS;
}
