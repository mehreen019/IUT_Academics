%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yylex(void);
void yyerror(const char *s);
extern int yylineno;
extern FILE *yyin;

static int tempCount = 0;  


char *newTemp(void) {
    char buf[32];
    tempCount++;
    snprintf(buf, sizeof(buf), "T%d", tempCount);
    return strdup(buf);
}

static void emit3(const char *op, const char *dest, const char *src1, const char *src2) {
    printf("%s %s, %s, %s\n", op, dest, src1, src2);
}

static void emit2(const char *op, const char *dest, const char *src1) {
    printf("%s %s, %s\n", op, dest, src1);
}

int hadError = 0;

%}

%union {
    char *str;
}

%token <str> ID
%token <str> NUMBER
%token PLUS MINUS TIMES DIVIDE MOD
%token ASSIGN SEMI LPAREN RPAREN

%type <str> Expr Term Factor

%left PLUS MINUS
%left TIMES DIVIDE MOD

%%

Program
    : StmtList
        {}
    ;

StmtList
    : StmtList Stmt
    | Stmt
    ;

Stmt
    : ID ASSIGN Expr SEMI
        {
            emit2("MOV", $1, $3);
            free($1);
            free($3);
        }
    | error SEMI
        {
            fprintf(stderr, "Syntax error: skipping malformed statement (line %d)\n", yylineno);
            hadError = 1;
            yyerrok;
        }
    ;

Expr
    : Expr PLUS Term
        {
            $$ = newTemp();
            emit3("ADD", $$, $1, $3);
            free($1);
            free($3);
        }
    | Expr MINUS Term
        {
            $$ = newTemp();
            emit3("SUB", $$, $1, $3);
            free($1);
            free($3);
        }
    | Term
        {
            $$ = $1;
        }
    ;

Term
    : Term TIMES Factor
        {
            $$ = newTemp();
            emit3("MUL", $$, $1, $3);
            free($1);
            free($3);
        }
    | Term DIVIDE Factor
        {
            $$ = newTemp();
            emit3("DIV", $$, $1, $3);
            free($1);
            free($3);
        }
    | Term MOD Factor
        {
            $$ = newTemp();
            emit3("MOD", $$, $1, $3);
            free($1);
            free($3);
        }
    | Factor
        {
            $$ = $1;
        }
    ;

Factor
    : LPAREN Expr RPAREN
        {
            $$ = $2;
        }
    | ID
        {
            $$ = $1;
        }
    | NUMBER
        {
            $$ = $1;
        }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Syntax error at line %d: %s\n", yylineno, s);
    hadError = 1;
}

int main(int argc, char **argv) {
    if (argc > 1) {
        FILE *f = fopen(argv[1], "r");
        if (!f) {
            fprintf(stderr, "Error: could not open input file '%s'\n", argv[1]);
            return 1;
        }
        yyin = f;
    }

    yyparse();

    if (argc > 1) {
        fclose(yyin);
    }

    return hadError ? 1 : 0;
}
