%{
#include <stdio.h>
#include <stdlib.h>

#include "heading.h"
#include "bison.h"
int yyerror(char *s);
//int yylineno = 1;
%}

digit		[0-9]
int_const	{digit}+

%%

{int_const}	{ yylval.int_val = atoi( yytext );     return INTEGER_LITERAL; }
"+"		{ yylval.op_val = yytext; return PLUS; }
"*"		{ yylval.op_val = yytext; return MULT; }

[ \t]*		{}
[\n]		{ yylineno++;	}

.		{ fputs( "scanner ", stderr ); yyerror(""); exit(EXIT_FAILURE); }
