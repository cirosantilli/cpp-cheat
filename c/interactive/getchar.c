/* Get on character from stdin.
 *
 * Same as getc(stdin).
 *
 * You have to press enter for the character to go through:
 * https://stackoverflow.com/questions/1798511/how-to-avoid-pressing-enter-with-getchar
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    printf("%c\n", getchar());
    return EXIT_SUCCESS;
}
