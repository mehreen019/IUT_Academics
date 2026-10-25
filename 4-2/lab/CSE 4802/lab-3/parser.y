%{
#include <stdio.h>   
#include <stdlib.h> 
#include <math.h>   

void yyerror(const char *s); 
int yylex();                  
%}

%union {
    double dval;
}

%token <dval> NUMBER

%token SIN COS TAN SQRT LOG

%type <dval> expr term power factor

%%

input:
    input line
    |
    ;

line:
    '\n'
    | expr '\n'
    {
        printf("Result = %lf\n", $1);
    }
    ;

expr:
    expr '+' term
    {
        $$ = $1 + $3;
    }
    | expr '-' term
    {
        $$ = $1 - $3;
    }
    | term
    {
        $$ = $1;
    }
    ;

term:
    term '*' power
    {
        $$ = $1 * $3;
    }
    | term '/' power
    {
        if ($3 == 0) {
            printf("Error: Division by zero\n");
            $$ = 0;
        } else {
            $$ = $1 / $3;
        }
    }
    | power
    {
        $$ = $1;
    }
    ;

power:
    factor '^' power
    {
        $$ = pow($1, $3);
    }
    | factor
    {
        $$ = $1;
    }
    ;

factor:
    SIN '(' expr ')'
    {
        $$ = sin($3);
    }
    | COS '(' expr ')'
    {
        $$ = cos($3);
    }
    | TAN '(' expr ')'
    {
        $$ = tan($3);
    }
    | SQRT '(' expr ')'
    {
        if ($3 < 0) {
            printf("Error: Square root of negative number\n");
            $$ = 0;
        } else {
            $$ = sqrt($3);
        }
    }
    | LOG '(' expr ')'
    {
        if ($3 <= 0) {
            printf("Error: Logarithm of non-positive number\n");
            $$ = 0;
        } else {
            $$ = log($3);
        }
    }
    | '(' expr ')'
    {
        $$ = $2;
    }
    | NUMBER
    {
        $$ = $1;
    }
    ;

%%

void yyerror(const char *s)
{
    printf("Syntax Error: %s\n", s);
}

int main()
{
    printf("Enter Scientific Expression:\n");
    yyparse();
    return 0;
}