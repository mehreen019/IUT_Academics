%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void yyerror(const char *s);
int yylex();

/* ── SYMBOL TABLE ── */
/* Each entry in the table has a name and a value */
typedef struct {
    char name[64];
    double value;
} Symbol;

/* The table can hold up to 100 variables */
#define MAX_SYMBOLS 100
Symbol symtable[MAX_SYMBOLS];
int sym_count = 0;  /* how many variables are currently stored */

/* Look up a variable by name. Returns its value, or 0 if not found */
double sym_get(char *name) {
    for (int i = 0; i < sym_count; i++) {
        if (strcmp(symtable[i].name, name) == 0) {
            return symtable[i].value;
        }
    }
    printf("Warning: variable '%s' not defined, using 0\n", name);
    return 0.0;
}

/* Set a variable's value. If it exists, update it. If not, add it. */
void sym_set(char *name, double value) {
    for (int i = 0; i < sym_count; i++) {
        if (strcmp(symtable[i].name, name) == 0) {
            symtable[i].value = value;  /* update existing */
            return;
        }
    }
    /* not found — add new entry */
    if (sym_count < MAX_SYMBOLS) {
        strcpy(symtable[sym_count].name, name);
        symtable[sym_count].value = value;
        sym_count++;
    } else {
        printf("Error: Symbol table full\n");
    }
}

/* Save the symbol table to symbols.txt */
void sym_save() {
    FILE *f = fopen("symbols.txt", "w");
    if (!f) {
        printf("Error: Could not save symbols.txt\n");
        return;
    }
    for (int i = 0; i < sym_count; i++) {
        fprintf(f, "%s %lf\n", symtable[i].name, symtable[i].value);
    }
    fclose(f);
}

/* Load the symbol table from symbols.txt (called at startup) */
void sym_load() {
    FILE *f = fopen("symbols.txt", "r");
    if (!f) return;  /* file doesn't exist yet, that's fine */
    
    char name[64];
    double value;
    while (fscanf(f, "%s %lf", name, &value) == 2) {
        sym_set(name, value);
    }
    fclose(f);
}

/* Print the symbol table to the screen */
void sym_print() {
    printf("\n--- Symbol Table ---\n");
    for (int i = 0; i < sym_count; i++) {
        printf("  %s = %lf\n", symtable[i].name, symtable[i].value);
    }
    printf("--------------------\n\n");
}

%}

%union {
    double dval;   /* for INTEGER, DOUBLE, and expression values */
    char  *sval;   /* for ID (variable names are strings) */
}

%token <dval> INTEGER DOUBLE
%token <sval> ID
%token SIN COS TAN SQRT LOG

%type <dval> expr term power factor statement

%%

input:
    input line
    |
    ;

line:
    '\n'
    | statement '\n'
    {
        /* print result and show updated symbol table */
        printf("Result = %lf\n", $1);
        sym_print();
    }
    | error '\n'
    {
        /* recover from syntax errors gracefully */
        yyerrok;
    }
    ;

statement:
    ID '=' expr
    {
        /* Assignment: store the value and save to file */
        sym_set($1, $3);
        sym_save();
        printf("Assigned: %s = %lf\n", $1, $3);
        $$ = $3;
        free($1);  /* free the string allocated by strdup in FLEX */
    }
    | expr
    {
        $$ = $1;
    }
    ;

expr:
    expr '+' term   { $$ = $1 + $3; }
    | expr '-' term { $$ = $1 - $3; }
    | term          { $$ = $1; }
    ;

term:
    term '*' power  { $$ = $1 * $3; }
    | term '/' power {
        if ($3 == 0) { printf("Error: Division by zero\n"); $$ = 0; }
        else { $$ = $1 / $3; }
    }
    | power         { $$ = $1; }
    ;

power:
    factor '^' power { $$ = pow($1, $3); }
    | factor         { $$ = $1; }
    ;

factor:
    SIN '(' expr ')'   { $$ = sin($3); }
    | COS '(' expr ')' { $$ = cos($3); }
    | TAN '(' expr ')' { $$ = tan($3); }
    | SQRT '(' expr ')' {
        if ($3 < 0) { printf("Error: sqrt of negative\n"); $$ = 0; }
        else { $$ = sqrt($3); }
    }
    | LOG '(' expr ')' {
        if ($3 <= 0) { printf("Error: log of non-positive\n"); $$ = 0; }
        else { $$ = log($3); }
    }
    | '(' expr ')'  { $$ = $2; }
    | INTEGER       { $$ = $1; }
    | DOUBLE        { $$ = $1; }
    | ID            {
        /* look up the variable's value from the symbol table */
        $$ = sym_get($1);
        free($1);
    }
    ;

%%

void yyerror(const char *s) {
    printf("Syntax Error: %s\n", s);
}

int main() {
    printf("Scientific Calculator with Variables\n");
    printf("=====================================\n");
    
    sym_load();  /* load any previously saved variables */
    
    if (sym_count > 0) {
        printf("Loaded previous session:\n");
        sym_print();
    }
    
    yyparse();
    return 0;
}