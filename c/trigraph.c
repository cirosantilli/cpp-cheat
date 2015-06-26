/*
# trigraphs

    Absolutelly obscure feature for very old systems which do not support certain
    characters or because of keyboards which don't support them easily

    It is so obscure that gcc:

    - turns them off by default without the `-trigraphs` flag
    - emits a warning if you use those in that case

    Is the first substitution made to source, even before the preprocessor.

    They are commented out here so that compilers like
    gcc won't annoy us with warnings.
*/

#include "common.h"

int main() {
    assert('??=' == '#');
    assert('??(' == '[');
    /* TODO literal backslash? */
    assert('\??/' == '\\');
    assert('??)' == ']');
    assert('??'' == '^');
    assert('??<' == '{');
    assert('??!' == '|');
    assert('??>' == '}');
    assert('??-' == '~');

    /*
    To avoid trigraphs on string literals:

    - use `\?`. It exists for that purpose.
    - use string concatenation
    */
    assert("\?\?" == "?" "?");

    return EXIT_SUCCESS;
}
