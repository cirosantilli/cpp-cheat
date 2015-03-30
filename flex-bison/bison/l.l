%{
#include "h.h"
#include "y.h"
void yyerror(char *);
%}

%%

    /* the only thing that is obligatory is that:
    
        - each rule will return an int identifier

            these are identified on the .y file by on of the directives:
            
            - %token
            - %left
            - %right

            but can also be a single char int's value in case of single char operators like '+'

        optional actions include:

        - set yylval.op_val to facilitate debuggint

        - if a value is calculable already (integers, floats)
            set

    */

[a-z]       { 
                yylval.sIndex = *yytext - 'a';
                return VARIABLE;
            }

    /* in c, integers that start with  0 except 0 are octal */

0           {
                yylval.iValue = atoi(yytext);
                return INTEGER;
            }

[1-9][0-9]* {
                yylval.iValue = atoi(yytext);
                return INTEGER;
            }

    /* single char symbols are returned as their own int value */

[-()<>=+*/;{}.] {
                return *yytext;
             }

    /* multi char tokens must return ints defined by the token directives inside the .y file  */

">="            return GE;
"<="            return LE;
"=="            return EQ;
"!="            return NE;
"while"         return WHILE;
"if"            return IF;
"else"          return ELSE;
"print"         return PRINT;

    /* do nothing on whitespace. tab is not allowed! */
[ ]+        ; 

[\n]        { yylineno++; }

.  { yyerror("bad char"); }

%%

int yywrap(void) {
    return 1;
}
