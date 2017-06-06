/*
http://stackoverflow.com/questions/12444679/poll-function-in-c-how-does-it-work

    ./poll.sh

Now:

- any further writes on "poll*.tmp" will be ignored. This could be easily fixed by re-opening them from here.
- this program hangs forever on poll. This could be easily fixed by counting how many fds are left.

Bibliography:

- http://www.linux-mag.com/id/357/
- https://www.ibm.com/support/knowledgecenter/en/ssw_i5_54/rzab6/poll.htm
*/

#include "common.h"

int main(void) {
    enum { N = 2 };
    char buf[1024], path[1024];
    int fd, i, n;
    struct pollfd pfds[N];

    for (i = 0; i < N; ++i) {
        snprintf(path, sizeof(path), "poll%d.tmp", i);
        /* O_NONBLOCK is required or else the open blocks
         * until the other side of the pipe opens. */
        fd = open(path, O_RDONLY | O_NONBLOCK);
        if (fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }
        pfds[i].fd = fd;
        /* Only events in this mask will be listened to.
         * However, there are also some events that are unmaskable,
         * notably POLLHUP when pipe closes! */
        pfds[i].events = POLLIN;
    }
    while (1) {
        puts("loop");
        i = poll(pfds, N, -1);
        if (i == -1) {
            perror("poll");
            exit(EXIT_FAILURE);
        }
        for (i = 0; i < N; ++i) {
            if (pfds[i].revents & POLLIN) {
                n = read(pfds[i].fd, buf, sizeof(buf));
                printf("i=%d n=%d buf=%.*s\n", i, n, n, buf);
            }
            if (pfds[i].revents & POLLHUP) {
                /* This happens when the other side closed.
                 * This event is only cleared when we close the reader. */

                /* poll won't set POLLHUP anymore once all fds are closed.
                 * Any futher polls on this will give the POLLNVAL event instead. */
                close(pfds[i].fd);

                /* negative fds are ignored. So if we negate an FD,
                 * we can both turn if off for a while, and turn it on
                 * later on by re-nagating it. */
                pfds[i].fd *= -1;
            }
        }
    }
}
