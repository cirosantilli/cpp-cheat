/*
http://stackoverflow.com/questions/15057010/comparing-version-numbers-in-c/37015135#37015135
*/

#define _GNU_SOURCE
#include <assert.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    assert(strverscmp("1.2.3" , "1.2.3" ) == 0);
    assert(strverscmp("1.2.3" , "1.2.4" )  < 0);
    assert(strverscmp("1.2.3" , "1.2.2" )  > 0);
    assert(strverscmp("9.2.3" , "10.2.3")  < 0);
    assert(strverscmp("10.2.3", "9.2.3" )  > 0);

    /* Delimiers are also compared. */
    assert(strverscmp("1a2", "1b2" ) < 0);
    assert(strverscmp("1b2", "1a2" ) > 0);

    /* Leading 0s: number gets treated as 0.X, e.g. 01 means 0.1.
     * Maybe not perfect for version strings, but sane version strings
     * should not have trailing 0s.
     */
    assert(strverscmp("01", "9" ) < 0);
    assert(strverscmp("01", "09") < 0);
    assert(strverscmp("01", "09") < 0);
    assert(strverscmp("09", "1")  < 0);
    return EXIT_SUCCESS;
}
