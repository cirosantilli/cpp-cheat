#include <stdio.h>

#include <string.h>
#include <ctype.h> //for isspace and family
#include <stdbool.h>

#include <stdlib.h>

#include <limits.h> //for [LONG|INT]_[MIN|MAX]
#include <math.h> //for HUGE_VALF
#include <float.h> //for FLT_[MIN|MAX]

#include <errno.h> //for erno

/* discard sdtin content up to first newline.
if there is no newline, waits for a newline to be input.*/
void flush_stdin_to_newline()
{

    char junk[16];
    do
    {
        fgets(junk,16,stdin);
    } while ( junk[strlen(junk)-1]!='\n' );

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
void ugstr(char* out, int max)
{

    bool done=false;
    while(!done)
    {
        fgets(out, max, stdin);

        char *newline = strchr(out, '\n'); /* search for newline character */
        if ( newline == NULL ) //no newline. too much input. reask.
        {
            flush_stdin_to_newline();
            fprintf(stderr, "input too large. max %d chars. reenter and press <enter>:\n", max);
        } else {
            *newline = '\0'; /* overwrite trailing newline */
            done = true;
        }

    }

}

/*
 * prompting user for input
 *
 * use only for very simple inputs,
 * since there is no possibility for undo here.
 *
 * for anything slighty more complicated, go for
 * ncurses or a gtk interface
 *
 */

/* user prompt string until newline
 *
 * same as ugstr, but writes user prompt to stderr
 */
void upstr(char* out, int max)
{

    fprintf(stderr, "enter a string and press <enter> (max %d chars):\n", max-1);
    fflush(stderr); /* http://c-faq.com/stdio/fflush.html */

    ugstr(out,max);

}

typedef enum { S2NSUCCESS, S2NOVERFLOW, S2NUNDERFLOW, S2NINCONVERTIBLE } STR2NUM_ERROR;
// S2N prefix so as not to conflict with OVERFLOW and UNDEFLOW of math

/* 
* converts string s to int i (output in i), supposing it is base base
*
* max base = 36
*
* returns STR2NUM_ERRORs accordingly
*
* in case of an error, the input int is not modified
*
* any whitespace in input will return S2NINCONVERTIBLE
*
* test in/out:
*
*    "10" 10
*    "-10" -10
*    "10." S2NINCONVERTIBLE
*    "10.0" S2NINCONVERTIBLE
*    "10.0e10" S2NINCONVERTIBLE
*    "a10" S2NINCONVERTIBLE
*    "10a" S2NINCONVERTIBLE
*    " 10" S2NINCONVERTIBLE
*    "10 " S2NINCONVERTIBLE
*    "1000000000000" S2NOVERFLOW (10^12 > int max)
*    "-1000000000000" S2NINCONVERTIBLE (-10^12 < int min)
*
*/
STR2NUM_ERROR str2int (int *i, char *s, int base)
{

    /* strict checking: must be EXACTLY an int */
    if(isspace(s[0]))
    {
        return S2NINCONVERTIBLE;
    }

    char *end;
    errno = 0;
    long l = strtol(s, &end, base);

    if ((errno == ERANGE && l == LONG_MAX) || l > INT_MAX)
    {
        return S2NOVERFLOW;
    }
    if ((errno == ERANGE && l == LONG_MIN) || l < INT_MIN)
    {
        return S2NUNDERFLOW;
    }
    if (*s == '\0' || *end != '\0')
    {
        return S2NINCONVERTIBLE;
    }
    *i = l;
    return S2NSUCCESS;
}

/*same as str2int, but prints errors to stderr*/
STR2NUM_ERROR str2int_stderr (int *i, char *s, int base)
{
    STR2NUM_ERROR out = str2int (i, s, base);
    if(out == S2NINCONVERTIBLE)
    {
        fprintf(stderr,"\"%s\" is not an int \n",s);
    }
    else if(out == S2NOVERFLOW)
    {
        fprintf(stderr,"\"%s\" is too large for an int. max value: %d\n",s,INT_MAX);
    }
    else if(out == S2NUNDERFLOW)
    {
        fprintf(stderr,"\"%s\" is too small for an int. min value: %d\n",s,INT_MIN);
    }
    return out;
}

/*user prompt c int in base b <= 36*/
int upint( int base )
{
    int out;
    STR2NUM_ERROR err;
    const int max=64;
    char in[max];

    while (1)
    {
        fprintf(stderr, "enter a integer and press <enter>:\n");
        fflush(stderr); /* http://c-faq.com/stdio/fflush.html */
        ugstr (in,max);
        err = str2int_stderr (&out, in, base);
        if ( err == S2NSUCCESS )
        {
            break;
        }
    }

    return out;
}

STR2NUM_ERROR str2float (float *fout, char *s)
{
    /* strict checking: must be EXACTLY an int */
    if(isspace(s[0]))
    {
        return S2NINCONVERTIBLE;
    }

    char *end;
    errno = 0;
    float f = strtof(s, &end);

    if ( errno == ERANGE && f == HUGE_VALF )
    {
        return S2NOVERFLOW;
    }
    if ( errno == ERANGE && f == -HUGE_VALF )
    {
        return S2NUNDERFLOW;
    }
    if (*s == '\0' || *end != '\0')
    {
        return S2NINCONVERTIBLE;
    }
    *fout = f;
    return S2NSUCCESS;
}

/*same as str2float, but prints errors to stderr*/
STR2NUM_ERROR str2float_stderr (float *f, char *s)
{
    STR2NUM_ERROR out = str2float (f, s);
    if(out == S2NINCONVERTIBLE)
    {
        fprintf(stderr,"\"%s\" is not a float \n",s);
    }
    else if(out == S2NOVERFLOW)
    {
        fprintf(stderr,"\"%s\" is too large for a float. max value: %f\n",s,FLT_MAX);
    }
    else if(out == S2NUNDERFLOW)
    {
        fprintf(stderr,"\"%s\" is too small for a float. min value: %f\n",s,FLT_MIN);
    }
    return out;
}


float upfloat ()
{
    float out;
    STR2NUM_ERROR err;
    const int max=64;
    char in[max];

    while (1)
    {
        fprintf (stderr, "enter a float and press <enter>:\n");
        fflush (stderr); /* http://c-faq.com/stdio/fflush.html */
        ugstr (in, max);
        err = str2float_stderr (&out, in);
        if ( err == S2NSUCCESS )
        {
            break;
        }
    }
    return out;
}

int main()
{
    /*const int l = 20;*/
    /*char str[l];*/
    /*upstr(str,l);*/
    /*printf("user entered:\n%s\n",str);*/

    /*int i;*/
    /*i = upint(10);*/
    /*printf("user entered:\n%d\n",i);*/

    float f;
    f = upfloat();
    printf ("user entered:\n%f\n", f);

    return 0;
}
