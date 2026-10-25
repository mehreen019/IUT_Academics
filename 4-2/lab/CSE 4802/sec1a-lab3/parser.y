%{
#include <stdio.h>
#include <stdlib.h>
void yyerror(const char *s);
int yylex();
%}

%token NUMBER

%%

input:
    input line
  |
  ;

line:
    '\n'
  | expr '\n'
    {
        printf("Result = %d\n", $1);
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
    term '*' factor
    {
        $$ = $1 * $3;
    }
  | term '/' factor
    {
        if ($3 == 0) {
            printf("Error: Division by zero\n");
            $$ = 0;
        } else {
            $$ = $1 / $3;
        }
    }
  | factor
    {
        $$ = $1;
    }
  ;

factor:
    factor '^' primary
    {
        int result = 1;
        for (int i = 0; i < $3; i++) result *= $1;
        $$ = result;
    }
  | primary
    {
        $$ = $1;
    }
  ;

primary:
    '(' expr ')'
    {
        $$ = $2;
    }
  | NUMBER
    {
        $$ = $1;
    }
  ;

%%

void yyerror(const char *s) {
    printf("Syntax Error\n");
}

int main() {
    printf("Enter Expression:\n");
    yyparse();
    return 0;
}