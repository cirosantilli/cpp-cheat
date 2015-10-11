#include "common.h"

/* Discard sdtin content up to first newline.
if there is no newline, waits for a newline to be input.*/
void flush_stdin_to_newline() {

    char junk[16];
    do {
        if (fgets(junk, sizeof(junk), stdin) == NULL) {
            /* TODO deal with error proprely */
        }
    } while (junk[strlen( junk ) -1 ] != '\n');

}

/*
 * user get string until newline.
 *
 * fixed maximum size.
 *
 * no newline on output.
 *
 * prompt again until user inputs a string under maximun size.
 */
void ugstr(char* out, int max) {
    bool done=false;
    while(!done) {
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
void upstr(char* out, int max) {
    fprintf(stderr, "enter a string and press <enter> (max %d chars):\n", max-1);
    fflush(stderr);
    ugstr(out,max);
}

/*
This is not the canonical source for this function: it is somewhere else in this repo.
We just copy pasted it here because lazy for proprely sharing.
*/
typedef enum { S2NSUCCESS, S2NOVERFLOW, S2NUNDERFLOW, S2NINCONVERTIBLE } STR2NUM_ERROR;
STR2NUM_ERROR str2int(int *i, char *s, int base) {
    if (isspace(s[0])) {
        return S2NINCONVERTIBLE;
    }
    char *end;
    errno = 0;
    long l = strtol(s, &end, base);
    if ((errno == ERANGE && l == LONG_MAX) || l > INT_MAX) {
        return S2NOVERFLOW;
    }
    if ((errno == ERANGE && l == LONG_MIN) || l < INT_MIN) {
        return S2NUNDERFLOW;
    }
    if (*s == '\0' || *end != '\0') {
        return S2NINCONVERTIBLE;
    }
    *i = l;
    return S2NSUCCESS;
}

/* Same as str2int, but prints errors to stderr. */
STR2NUM_ERROR str2int_stderr(int *i, char *s, int base) {
    STR2NUM_ERROR out = str2int (i, s, base);
    if (out == S2NINCONVERTIBLE) {
        fprintf(stderr,"\"%s\" is not an int \n",s);
    } else if (out == S2NOVERFLOW) {
        fprintf(stderr,"\"%s\" is too large for an int. max value: %d\n",s,INT_MAX);
    } else if (out == S2NUNDERFLOW) {
        fprintf(stderr,"\"%s\" is too small for an int. min value: %d\n",s,INT_MIN);
    }
    return out;
}

/* User prompt c int in base b <= 36. */
int upint(int base) {
    int out;
    STR2NUM_ERROR err;
    const int max=64;
    char in[max];

    while (1) {
        fprintf(stderr, "enter a integer and press <enter>:\n");
        fflush(stderr);
        ugstr (in,max);
        err = str2int_stderr(&out, in, base);
        if (err == S2NSUCCESS) {
            break;
        }
    }

    return out;
}

STR2NUM_ERROR str2float(float *fout, char *s) {
    /* strict checking: must be EXACTLY an int */
    if(isspace(s[0])) {
        return S2NINCONVERTIBLE;
    }

    char *end;
    errno = 0;
    float f = strtof(s, &end);

    if ( errno == ERANGE && f == HUGE_VALF ) {
        return S2NOVERFLOW;
    }
    if ( errno == ERANGE && f == -HUGE_VALF ) {
        return S2NUNDERFLOW;
    }
    if (*s == '\0' || *end != '\0') {
        return S2NINCONVERTIBLE;
    }
    *fout = f;
    return S2NSUCCESS;
}

/*same as str2float, but prints errors to stderr*/
STR2NUM_ERROR str2float_stderr(float *f, char *s) {
    STR2NUM_ERROR out = str2float (f, s);
    if(out == S2NINCONVERTIBLE) {
        fprintf(stderr,"\"%s\" is not a float \n",s);
    } else if(out == S2NOVERFLOW) {
        fprintf(stderr,"\"%s\" is too large for a float. max value: %f\n",s,FLT_MAX);
    } else if(out == S2NUNDERFLOW) {
        fprintf(stderr,"\"%s\" is too small for a float. min value: %f\n",s,FLT_MIN);
    }
    return out;
}


float upfloat() {
    float out;
    STR2NUM_ERROR err;
    const int max=64;
    char in[max];

    while (1) {
        fprintf(stderr, "enter a float and press <enter>:\n");
        fflush(stderr);
        ugstr(in, max);
        err = str2float_stderr (&out, in);
        if (err == S2NSUCCESS) {
            break;
        }
    }
    return out;
}

int main() {
    const int l = 20;
    int i;
    float f;
    if (0) {
        char str[l];
        upstr(str,l);
        printf("user entered:\n%s\n",str);

        i = upint(10);
        printf("user entered:\n%d\n",i);

        f = upfloat();
        printf ("user entered:\n%f\n", f);
    }
    return 0;
}
