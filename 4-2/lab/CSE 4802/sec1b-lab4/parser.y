%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(const char *s);
int yylex(void);

#define MAX_VARS 100

typedef struct {
    char name[64];
    double value;
} Var;

Var symtab[MAX_VARS];
int symtab_size = 0;

void save_symbols(void) {
    FILE *fp = fopen("symbols.txt", "w");
    if (!fp) return;
    for (int i = 0; i < symtab_size; i++) {
        fprintf(fp, "%s %lf\n", symtab[i].name, symtab[i].value);
    }
    fclose(fp);
}

void load_symbols(void) {
    FILE *fp = fopen("symbols.txt", "r");
    if (!fp) return;
    char name[64];
    double value;
    while (fscanf(fp, "%s %lf", name, &value) == 2) {
        strcpy(symtab[symtab_size].name, name);
        symtab[symtab_size].value = value;
        symtab_size++;
    }
    fclose(fp);
}

void setvar(char *name, double value) {
    for (int i = 0; i < symtab_size; i++) {
        if (strcmp(symtab[i].name, name) == 0) {
            symtab[i].value = value;
            save_symbols();
            return;
        }
    }
    strcpy(symtab[symtab_size].name, name);
    symtab[symtab_size].value = value;
    symtab_size++;
    save_symbols();
}

double getvar(char *name) {
    for (int i = 0; i < symtab_size; i++) {
        if (strcmp(symtab[i].name, name) == 0) {
            return symtab[i].value;
        }
    }
    printf("Warning: undefined variable '%s', using 0\n", name);
    return 0;
}
%}

%union {
    double dval;
    char *sval;
}

%token <dval> INTEGER DOUBLE
%token <sval> ID
%type <dval> expr term factor statement

%%

input:
    input line
  |
  ;

line:
    '\n'
  | statement '\n'
  ;

statement:
    ID '=' expr
    {
        setvar($1, $3);
        printf("\nValue = %lf\n", $3);
        free($1);
        $$ = $3;
    }
  | expr
    {
        printf("\nValue = %lf\n", $1);
        $$ = $1;
    }
  ;

expr:
    expr '+' term
    {
        $$ = $1 + $3;
        printf("+ ");
    }
  | expr '-' term
    {
        $$ = $1 - $3;
        printf("- ");
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
        printf("* ");
    }
  | term '/' factor
    {
        if ($3 == 0) {
            printf("Error: Division by zero\n");
            $$ = 0;
        } else {
            $$ = $1 / $3;
        }
        printf("/ ");
    }
  | factor
    {
        $$ = $1;
    }
  ;

factor:
    '(' expr ')'
    {
        $$ = $2;
    }
  | INTEGER
    {
        printf("%g ", $1);
        $$ = $1;
    }
  | DOUBLE
    {
        printf("%g ", $1);
        $$ = $1;
    }
  | ID
    {
        printf("%s ", $1);
        $$ = getvar($1);
        free($1);
    }
  ;

%%

void yyerror(const char *s) {
    printf("Syntax Error\n");
}

int main() {
    load_symbols();
    printf("Enter statements (ID = expr, or just expr):\n");
    yyparse();
    return 0;
}