/* Loop forever. When you hit Ctrl + C, print how many times we have hit Ctrl + C so far.
 *
 * This has to be in POSIX because we can't do stdout output.
 *
 * In POSIX however we have write, and we implement our own printf("%d").
 */

#define _XOPEN_SOURCE 700
#include <limits.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

volatile sig_atomic_t global = 0;

/* async-signal-safe implementation of integer to string conversion. */
size_t int_to_str(sig_atomic_t n, char *buf) {
    enum { base = 10 };
    char c;
    size_t size, left, right;
    if (n == 0) {
        buf[0] = '0';
        size = 1;
    } else {
        size = 0;
        while (n > 0) {
            switch (n % base) {
                case 0: c = '0'; break;
                case 1: c = '1'; break;
                case 2: c = '2'; break;
                case 3: c = '3'; break;
                case 4: c = '4'; break;
                case 5: c = '5'; break;
                case 6: c = '6'; break;
                case 7: c = '7'; break;
                case 8: c = '8'; break;
                case 9: c = '9'; break;
            }
            buf[size] = c;
            n /= base;
            size++;
        }
        right = 0;
        left = size - 1;
        while (right < left) {
            c = buf[right];
            buf[right] = buf[left];
            buf[left] = c;
            right++;
            left--;
        }
    }
    return size;
}

void signal_handler(int sig) {
    /* Overestimate and reserve 8 chars per byte.
     * With this size we could even print a binary string.
     */
    char buf[sizeof(sig_atomic_t) * CHAR_BIT + 1];
    size_t size = int_to_str(global, buf);
    buf[size] = '\n';
    write(STDOUT_FILENO, buf, size + 1);
    global += 1;
    signal(sig, signal_handler);
}

int main(void) {
    signal(SIGINT, signal_handler);
    while(1);
    return EXIT_SUCCESS;
}
