%{
#include <stdio.h>
#include "heading.h"
int yyerror(char *s);
int yylex(void);
%}

%union{
  int		int_val;
  char*	op_val;
}

%start	input 

%token	<int_val>	INTEGER_LITERAL
%type	<int_val>	exp
%left	PLUS
%left	MULT

%%

input:		/* empty */
		| exp	{ printf( "%d\n", $1 ); }
		;

exp:		INTEGER_LITERAL	{ $$ = $1; }
		| exp PLUS exp	{ $$ = $1 + $3; }
		| exp MULT exp	{ $$ = $1 * $3; }
		;

%%

int yyerror(char* s)
{
  extern int yylineno;	// defined and maintained in lex.c
  extern char* yytext;	// defined and maintained in lex.c
  
  fprintf( stderr, "error: %s at symbol \"%s\" on line %d", s, yytext, yylineno );
  exit(1);
}
