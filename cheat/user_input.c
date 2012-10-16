#include <string.h>
#include <stdbool.h>

#include <stdio.h>
#include <stdlib.h>
#include <limits.h> //for [LONG|INT][MIN|MAX]
#include <errno.h> //for erno

typedef enum { S2ISUCCESS, S2IOVERFLOW, S2IUNDERFLOW, S2IINCONVERTIBLE } STR2INT_ERROR;
// S2I prefix so as not to conflict with OVERFLOW and UNDEFLOW of math

/* 
* converts string s to int i (output in i), supposing it is base base
*
* max base = 36
*
* returns STR2INT_ERROR accordingly
*
* preceding whitespace is ignored. tailing whitespace will lead to an error.
*
* test in/out:
*
*  "10" 10
*  "-10" -10
*  "10." S2IINCONVERTIBLE
*  "10.0" S2IINCONVERTIBLE
*  "10.0e10" S2IINCONVERTIBLE
*  "a10" S2IINCONVERTIBLE
*  "10a" S2IINCONVERTIBLE
*  " 10" 10
*  "10 " S2IINCONVERTIBLE
*  "1000000000000" S2IOVERFLOW (10^12 > int max)
*  "-1000000000000" S2IINCONVERTIBLE (-10^12 < int min)
*
*/
STR2INT_ERROR str2int (int *i, char *s, int base)
{
  char *end;
  long  l;
  errno = 0;
  l = strtol(s, &end, base);

  if ((errno == ERANGE && l == LONG_MAX) || l > INT_MAX) {
    return S2IOVERFLOW;
  }
  if ((errno == ERANGE && l == LONG_MIN) || l < INT_MIN) {
    return S2IUNDERFLOW;
  }
  if (*s == '\0' || *end != '\0') {
    return S2IINCONVERTIBLE;
  }
  *i = l;
  return S2ISUCCESS;
}


/*same as str2int, but prints errors to stderr*/
STR2INT_ERROR str2int_stderr (int *i, char *s, int base)
{
  STR2INT_ERROR out = str2int (i, s, base);
  if(out == S2IINCONVERTIBLE){
    fprintf(stderr,"\"%s\" is not strtol int \n",s);
  } else if(out == S2IOVERFLOW){
    fprintf(stderr,"\"%s\" is too large for an int. max value: %d\n",s,INT_MAX);
  } else if(out == S2IUNDERFLOW){
    fprintf(stderr,"\"%s\" is too small for an int. min value: %d\n",s,INT_MIN);
  }
  return out;
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

/* discard sdtin content up to first newline.
if there is no newline, waits for a newline to be input.*/
void flush_stdin_to_newline(){

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
void ugstr(char* out, int max){

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

/*user prompt c int in base b <= 36*/
int upint( int base )
{

  int out;
  STR2INT_ERROR err;
  const int max=32;
  char in[max];

  while (1)
  {
    fprintf(stderr, "enter a strtol int and press <enter>:\n");
    fflush(stderr); /* http://c-faq.com/stdio/fflush.html */
    ugstr (in,max);
    err = str2int_stderr (&out, in, base);
    if ( err == S2ISUCCESS ){
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

      int i;
      STR2INT_ERROR err;
      err = str2int_stderr (&i, "12345681234568", 10);
      if ( err == S2ISUCCESS ){
        fprintf(stderr, "you entered:\n%d\n",i);
      }

      return 0;
}
