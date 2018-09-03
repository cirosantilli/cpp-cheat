/* Get a string, int and float from the user, with full error checking.
 *
 * Keep bugging the user until he enters properly formatted input.
 */

#include "common.h"
#include "../str2num.h"

/* Discard sdtin content up to first newline.
 * if there is no newline, waits for a newline to be input.
 */
void flush_stdin_to_newline() {
    char junk[16];
    do {
        if (fgets(junk, sizeof(junk), stdin) == NULL) {
            /* TODO deal with error proprely */
        }
    } while (junk[strlen( junk ) -1 ] != '\n');
}

/* user get string until newline.
 *
 * fixed maximum size.
 *
 * no newline on output.
 *
 * prompt again until user inputs a string under maximun size.
 */
void ugstr(char* out, int max) {
    bool done=false;
    while (!done) {
        if (fgets(out, max, stdin) == NULL) {
            /* TODO deal with error proprely */
        }
        char *newline = strchr(out, '\n'); /* search for newline character */
        if (newline == NULL) {
            /* No newline. too much input. reask. */
            flush_stdin_to_newline();
            fprintf(stderr, "input too large. max %d chars. reenter and press <enter>:\n", max);
        } else {
            *newline = '\0'; /* overwrite trailing newline */
            done = true;
        }
    }
}

/* user prompt string until newline
 *
 * same as ugstr, but writes user prompt to stderr
 */
void user_get_string(char* out, int max) {
    fprintf(stderr, "enter a string and press <enter> (max %d chars):\n", max-1);
    fflush(stderr);
    ugstr(out, max);
}

/* Same as str2int, but prints errors to stderr. */
str2num_errno str2int_stderr(int *i, char *s, int base) {
    str2num_errno out = str2int(i, s, base);
    if (out == STR2NUM_INCONVERTIBLE) {
        fprintf(stderr, "\"%s\" is not an int \n", s);
    } else if (out == STR2NUM_OVERFLOW) {
        fprintf(stderr, "\"%s\" is too large for an int. max value: %d\n", s, INT_MAX);
    } else if (out == STR2NUM_UNDERFLOW) {
        fprintf(stderr, "\"%s\" is too small for an int. min value: %d\n", s, INT_MIN);
    }
    return out;
}

/* User prompt c int in 2 <= base <= 36. */
int user_get_int(int base) {
    int out;
    str2num_errno err;
    enum { max = 64 };
    char in[max];
    while (1) {
        fprintf(stderr, "enter a integer and press <enter>:\n");
        fflush(stderr);
        ugstr(in, max);
        err = str2int_stderr(&out, in, base);
        if (err == STR2NUM_SUCCESS) {
            break;
        }
    }
    return out;
}

/* Same as str2float, but prints errors to stderr. */
str2num_errno str2float_stderr(float *f, char *s) {
    str2num_errno out = str2float(f, s);
    if(out == STR2NUM_INCONVERTIBLE) {
        fprintf(stderr, "\"%s\" is not a float \n", s);
    } else if(out == STR2NUM_OVERFLOW) {
        fprintf(stderr, "\"%s\" is too large for a float. max value: %f\n", s, FLT_MAX);
    } else if(out == STR2NUM_UNDERFLOW) {
        fprintf(stderr, "\"%s\" is too small for a float. min value: %f\n", s, FLT_MIN);
    }
    return out;
}

float user_get_float() {
    float out;
    str2num_errno err;
    enum { max = 64 };
    char in[max];
    while (1) {
        fprintf(stderr, "enter a float and press <enter>:\n");
        fflush(stderr);
        ugstr(in, max);
        err = str2float_stderr (&out, in);
        if (err == STR2NUM_SUCCESS) {
            break;
        }
    }
    return out;
}

int main(void) {
    int i;
    float f;
    char str[4];

    user_get_string(str, sizeof(str));
    printf("user entered:\n%s\n\n", str);

    i = user_get_int(10);
    printf("user entered:\n%d\n\n", i);

    f = user_get_float();
    printf ("user entered:\n%f\n\n", f);

    return EXIT_SUCCESS;
}
