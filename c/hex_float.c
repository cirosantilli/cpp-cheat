/* # float hex literal
 *
 * E.g.:
 *
 *     0xA.8p10
 *
 * Equals:
 *
 *     1010.1000 * 2^10 = 10.5 x 2^10
 *
 * The exponent is given *in decimal*.
 */

#include "common.h"

int main(void) {
#if __STDC_VERSION__ >= 199901L
    /* Non leading one form. */
    assert(0xA.0p0  ==   10.0);
    assert(0x1.4p3  ==   10.0);
    assert(0xA.8p0  ==   10.5);
    assert(0x1.8p1  ==    3.0);
    assert(0x1.0p10 == 1024.0);
    /* There is no octal float literal: */
#if 0
    /*float f = 01.2p3;*/
#endif
#endif
    return EXIT_SUCCESS;
}
