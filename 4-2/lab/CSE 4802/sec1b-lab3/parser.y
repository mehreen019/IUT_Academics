%{
#include <stdio.h>
#include <stdlib.h>
void yyerror(const char *s);
int yylex();
%}

%union {
    char *sval;
}
%token <sval> ID

%%

input:
    input line
  |
  ;

line:
    '\n'
  | expr '\n'
    {
        printf("\n");
    }
  ;

expr:
    expr '+' term
    {
        printf("+");
    }
  | expr '-' term
    {
        printf("-");
    }
  | term
  ;

term:
    term '*' power
    {
        printf("*");
    }
  | term '/' power
    {
        printf("/");
    }
  | power
  ;

power:
    factor '^' power
    {
        printf("^");
    }
  | factor
  ;

factor:
    '(' expr ')'
  | ID
    {
        printf("%s", $1);
        free($1);
    }
  ;

%%

void yyerror(const char *s) {
    printf("Syntax Error\n");
}

int main() {
    printf("Enter Infix Expression:\n");
    yyparse();
    return 0;
}