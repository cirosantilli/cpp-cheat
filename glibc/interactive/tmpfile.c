/*
https://stackoverflow.com/questions/4508998/what-is-anonymous-inode/44388030#44388030
*/

#include "common.h"

int main(void) {
    char buf[]  = { 'a', 'b', 'c', 'd' };
    char buf2[]  = { 'e', 'f', 'g', 'h' };
    int f, ret;
    size_t off;

    /* write */
    f = open(".", O_TMPFILE | O_RDWR, S_IRUSR | S_IWUSR);
    ret = write(f, buf, sizeof(buf));

    /* Let user interactivelly check if anything changed on directory. */
    /*puts("hit enter to continue");*/
    /*getchar();*/

    /* read */
    lseek(f, 0, SEEK_SET);
    off = 0;
    while ((ret = read(f, buf2 + off, sizeof(buf) - off))) {
        off += ret;
    }
    close(f);
    assert(!memcmp(buf, buf2, sizeof(buf)));

    return EXIT_SUCCESS;
}
