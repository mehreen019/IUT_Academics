%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int  yylex(void);
void yyerror(const char *s);
extern FILE *yyin;

/* ---------- hard-coded schema ---------- */
char *tables[]  = { "Student", "Employee", NULL };
char *studentC[] = { "ID", "Name", "Age", "CGPA", NULL };
char *employeeC[]= { "EmpID", "Name", "Salary", NULL };

char table[64];          /* table named in the FROM clause */
char *sel[16]; int nsel = 0;   /* SELECT columns, checked later */
int  err = 0;            /* semantic errors in this query */

int tableExists(char *t) {
    int i;
    for (i = 0; tables[i]; i++) if (!strcmp(tables[i], t)) return 1;
    return 0;
}
int columnExists(char *t, char *c) {
    char **list = NULL; int i;
    if (!strcmp(t, "Student"))  list = studentC;
    if (!strcmp(t, "Employee")) list = employeeC;
    if (!list) return 1;                    /* unknown table: already reported */
    for (i = 0; list[i]; i++) if (!strcmp(list[i], c)) return 1;
    return 0;
}
void checkColumn(char *c) {
    if (!columnExists(table, c)) {
        printf("Semantic Error: Column '%s' does not exist in table '%s'.\n", c, table);
        err = 1;
    }
}
%}

%union { char *str; }
%token <str> IDENTIFIER
%token SELECT FROM WHERE ORDER BY AND OR
%token STAR COMMA SEMICOLON RELOP
%token INTEGER_LITERAL DOUBLE_LITERAL STRING_LITERAL

%%

query
    : SELECT select_list FROM table_name where_clause order_clause SEMICOLON
        {
            int i;
            for (i = 0; i < nsel; i++) checkColumn(sel[i]);   /* now table is known */
            if (!err) printf("Valid SQL statement.\n");
        }
    ;

select_list
    : STAR
    | column_list
    ;

column_list
    : column_list COMMA IDENTIFIER   { if (nsel < 16) sel[nsel++] = $3; }
    | IDENTIFIER                     { if (nsel < 16) sel[nsel++] = $1; }
    ;

table_name
    : IDENTIFIER
        {
            strcpy(table, $1);
            if (!tableExists($1)) {
                printf("Semantic Error: Table '%s' does not exist.\n", $1);
                err = 1;
            }
        }
    ;

where_clause
    : /* empty */
    | WHERE condition
    ;

condition
    : condition logical_op simple_condition
    | simple_condition
    ;

simple_condition
    : IDENTIFIER RELOP value         { checkColumn($1); }
    ;

logical_op
    : AND
    | OR
    ;

value
    : INTEGER_LITERAL
    | DOUBLE_LITERAL
    | STRING_LITERAL
    | IDENTIFIER
    ;

order_clause
    : /* empty */
    | ORDER BY IDENTIFIER            { checkColumn($3); }
    ;

%%

void yyerror(const char *s)
{
    printf("Syntax Error: %s\n", s);
}

int main(int argc, char **argv)
{
    if (argc > 1) yyin = fopen(argv[1], "r");
    yyparse();
    return 0;
}
