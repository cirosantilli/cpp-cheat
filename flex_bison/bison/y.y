/* my major bison cheat */

/* definitions section */

%{
/* #code section
    
    goes to bison header untouched
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "h.h"

/* prototypes */
nodeType *opr(int oper, int nops, ...);
nodeType *id(int i);
nodeType *con(int value);
void freeNode(nodeType *p);
int ex(nodeType *p);
int yylex(void);

void yyerror(char *s);
int sym[26];                    /* symbol table */
%}

    /* 
        #union

        tokens directives will define integers that identify tokens
    */

%union {
    int iValue;                 /* integer value */
    char sIndex;                /* symbol table index */
    nodeType *nPtr;             /* node pointer */
};
    /* 
        #token

        tokens directives will define integers that identify tokens
    */

%token <iValue> INTEGER
%token <sIndex> VARIABLE
%token WHILE IF PRINT

    /* 
        #nonassoc

        TODO
    */
%nonassoc IFX
%nonassoc ELSE

    /* 
        #left

        left associative tokens: 1 - 2 - 3 = ( 1 - 2 ) - 3
        
        order of lefts gives operator precedence. here:

        - GE and LE have the same precedence
        - GE has lower precedence than '+'

        #single char

        single char tokens like '+' may be representade safely by their char's int value
    */
%left GE LE EQ NE '>' '<'
%left '+' '-'
%left '*' '/'
%nonassoc UMINUS

%type <nPtr> stmt expr stmt_list

%%
    /*
        #rules section

        bnf generation
    */

    /*
        #stack

        as tokens are read they are put on a stack

        when a rule is used, it consumes part of the stack

        $1: value of the symbol at the top of hte stack

        $2: 2nd

        $3: 3rd

        ...

        $$: value of the symbol that will be put on the stack
    */

program:    /* with this line, empty program is fine */
        function                { /*exit(EXIT_SUCCESS);*/ }
        ;

function:
          function stmt         { ex($2); freeNode($2); }
        | /* NULL */
        ;

stmt:
          ';'                            { $$ = opr(';', 2, NULL, NULL); }
        | expr ';'                       { $$ = $1; }
        | PRINT expr ';'                 { $$ = opr(PRINT, 1, $2); }
        | VARIABLE '=' expr ';'          { $$ = opr('=', 2, id($1), $3); }
        | WHILE '(' expr ')' stmt        { $$ = opr(WHILE, 2, $3, $5); }
        | IF '(' expr ')' stmt %prec IFX { $$ = opr(IF, 2, $3, $5); }
        | IF '(' expr ')' stmt ELSE stmt { $$ = opr(IF, 3, $3, $5, $7); }
        | '{' stmt_list '}'              { $$ = $2; }
        ;

stmt_list:
          stmt                  { $$ = $1; }
        | stmt_list stmt        { $$ = opr(';', 2, $1, $2); }
        ;

        /*
            #why $1 + $3??

            because $2 is the value of the second token
            on the stack, which is the '+' token! we need
            the value of the 3rd symbol of the stack.
        */

expr:
          INTEGER               { $$ = con($1); }
        | VARIABLE              { $$ = id($1); }
        | '-' expr %prec UMINUS { $$ = opr(UMINUS, 1, $2); }
        | expr '+' expr         { $$ = opr('+', 2, $1, $3); }
        | expr '-' expr         { $$ = opr('-', 2, $1, $3); }
        | expr '*' expr         { $$ = opr('*', 2, $1, $3); }
        | expr '/' expr         { $$ = opr('/', 2, $1, $3); }
        | expr '<' expr         { $$ = opr('<', 2, $1, $3); }
        | expr '>' expr         { $$ = opr('>', 2, $1, $3); }
        | expr GE expr          { $$ = opr(GE, 2, $1, $3); }
        | expr LE expr          { $$ = opr(LE, 2, $1, $3); }
        | expr NE expr          { $$ = opr(NE, 2, $1, $3); }
        | expr EQ expr          { $$ = opr(EQ, 2, $1, $3); }
        | '(' expr ')'          { $$ = $2; }
        ;

%%

/* subroutines section. back to c world. */

nodeType *con(int value)
{
    nodeType *p;

    /* allocate node */
    if ((p = malloc(sizeof(nodeType))) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeCon;
    p->con.value = value;

    return p;
}

nodeType *id(int i)
{
    nodeType *p;

    /* allocate node */
    if ((p = malloc(sizeof(nodeType))) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeId;
    p->id.i = i;

    return p;
}

nodeType *opr(int oper, int nops, ...)
{
    va_list ap;
    nodeType *p;
    int i;

    /* allocate node */
    if ((p = malloc(sizeof(nodeType))) == NULL)
        yyerror("out of memory");
    if ((p->opr.op = malloc(nops * sizeof(nodeType))) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeOpr;
    p->opr.oper = oper;
    p->opr.nops = nops;
    va_start(ap, nops);
    for (i = 0; i < nops; i++)
        p->opr.op[i] = va_arg(ap, nodeType*);
    va_end(ap);
    return p;
}

void freeNode(nodeType *p)
{
    int i;

    if (!p) return;
    if (p->type == typeOpr) {
        for (i = 0; i < p->opr.nops; i++)
            freeNode(p->opr.op[i]);
		free (p->opr.op);
    }
    free (p);
}

void yyerror(char* s)
{
    //defined and maintained in flex file
    extern int yylineno;
    extern char* yytext;
    
    fprintf( stderr, "error:\n  line: %d\n  type: %s\n",  yylineno, s );
    /*exit(EXIT_FAILURE);*/
}

int main(int argc, char **argv)
{
    /* file io. forgot how, think there is some easy way. TODO */
    if ( (argc > 1) )
    {
        /*yyin = fopen( argv[1], "r" );*/
        /*if( yyin == NULL )*/
        /*{*/
            /*fprintf( stderr, "file:\n%s\ncannot be opened\n", argv[1] );*/
            /*exit( EXIT_FAILURE );*/
        /*}*/
    }
    
    yyparse();

    return EXIT_SUCCESS;
}
