/* Write integers from a signal handler in an async signal safe way:
 *
 * - https://stackoverflow.com/questions/16891019/how-to-avoid-using-printf-in-a-signal-handler/52145149#52145149
 * - https://stackoverflow.com/questions/14573000/print-int-from-signal-handler-using-write-or-async-safe-functions/52111436#52111436
 *
 * Just unit test that our async signal safe implementation of itoa works:
 *
 *     ./sigint.out
 *
 * Also loop forever. When you hit Ctrl + C, print how many times we have hit Ctrl + C so far:
 *
 *     ./sigint.out 1
 *
 * This has to be in POSIX because we can't do stdout output.
 *
 * In POSIX however we have write, and we implement our own printf("%d").
 */

#define _XOPEN_SOURCE 700
#include <assert.h>
#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

/* Calculate the minimal buffer size for a given type.
 *
 * Here we overestimate and reserve 8 chars per byte.
 *
 * With this size we could even print a binary string.
 *
 * - +1 for NULL terminator
 * - +1 for '-' sign
 *
 * A tight limit for base 10 can be found at:
 * https://stackoverflow.com/questions/8257714/how-to-convert-an-int-to-string-in-c/32871108#32871108
 *
 * TODO: get tight limits for all bases, possibly by looking into
 * glibc's atoi: https://stackoverflow.com/questions/190229/where-is-the-itoa-function-in-linux/52127877#52127877
 */
#define ITOA_SAFE_STRLEN(type) sizeof(type) * CHAR_BIT + 2

/* async-signal-safe implementation of integer to string conversion.
 *
 * Null terminates the output string.
 *
 * The input buffer size must be large enough to contain the output,
 * the caller must calculate it properly.
 *
 * @param[out] value  Input integer value to convert.
 * @param[out] result Buffer to output to.
 * @param[in]  base   Base to convert to.
 * @return     Pointer to the end of the written string.
 */
char *itoa_safe(intmax_t value, char *result, int base) {
    intmax_t tmp_value;
    char *ptr, *ptr2, tmp_char;
    if (base < 2 || base > 36) {
        return NULL;
    }

    ptr = result;
    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "ZYXWVUTSRQPONMLKJIHGFEDCBA9876543210123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[35 + (tmp_value - value * base)];
    } while (value);
    if (tmp_value < 0)
        *ptr++ = '-';
    ptr2 = result;
    result = ptr;
    *ptr-- = '\0';
    while (ptr2 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr2;
        *ptr2++ = tmp_char;
    }
    return result;
}

volatile sig_atomic_t global = 0;

void signal_handler(int sig) {
    char key_str[] = "count, sigid: ";
    /* This is exact:
     * - the null after the first int will contain the space
     * - the null after the second int will contain the newline
     */
    char buf[2 * ITOA_SAFE_STRLEN(sig_atomic_t) + sizeof(key_str)];
    enum { base = 10 };
    char *end;
    end = buf;
    strcpy(end, key_str);
    end += sizeof(key_str);
    end = itoa_safe(global, end, base);
    *end++ = ' ';
    end = itoa_safe(sig, end, base);
    *end++ = '\n';
    write(STDOUT_FILENO, buf, end - buf);
    global += 1;
    signal(sig, signal_handler);
}

int main(int argc, char **argv) {
    /* Unit test itoa_safe. */
    {
        typedef struct {
            intmax_t n;
            int base;
            char out[1024];
        } InOut;
        char result[1024];
        size_t i;
        InOut io;
        InOut ios[] = {
            /* Base 10. */
            {0, 10, "0"},
            {1, 10, "1"},
            {9, 10, "9"},
            {10, 10, "10"},
            {100, 10, "100"},
            {-1, 10, "-1"},
            {-9, 10, "-9"},
            {-10, 10, "-10"},
            {-100, 10, "-100"},

            /* Base 2. */
            {0, 2, "0"},
            {1, 2, "1"},
            {10, 2, "1010"},
            {100, 2, "1100100"},
            {-1, 2, "-1"},
            {-100, 2, "-1100100"},

            /* Base 35. */
            {0, 35, "0"},
            {1, 35, "1"},
            {34, 35, "Y"},
            {35, 35, "10"},
            {100, 35, "2U"},
            {-1, 35, "-1"},
            {-34, 35, "-Y"},
            {-35, 35, "-10"},
            {-100, 35, "-2U"},
        };
        for (i = 0; i < sizeof(ios)/sizeof(ios[0]); ++i) {
            io = ios[i];
            itoa_safe(io.n, result, io.base);
            if (strcmp(result, io.out)) {
                printf("%ju %d %s\n", io.n, io.base, io.out);
                assert(0);
            }
        }
    }

    /* Handle the signals. */
    if (argc > 1 && !strcmp(argv[1], "1")) {
        signal(SIGINT, signal_handler);
        while(1);
    }

    return EXIT_SUCCESS;
}
