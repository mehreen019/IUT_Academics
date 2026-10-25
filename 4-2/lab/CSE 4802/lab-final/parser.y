%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yylex(void);
void yyerror(const char *s);
extern int yylineno;
%}

%union {
    double dval;
    char *str;
}

%token <str> STRING
%token <dval> INTEGER DOUBLE
%token <str> BOOLEAN IDENT
%token LEFT_BRACKET RIGHT_BRACKET EQUALS NEWLINE

%%

ini:
    sections
    {
        printf("Configuration file is syntactically valid.\n");
    }
  ;

sections:
    sections section
    | section ;

section:
    LEFT_BRACKET IDENT RIGHT_BRACKET NEWLINE{
        free($2);
    }
    members
    | LEFT_BRACKET RIGHT_BRACKET NEWLINE{
        yyerror("A section name is required");
        YYERROR;
    }
    | LEFT_BRACKET IDENT NEWLINE{
        yyerror("The section header is incomplete, Expected ']'");
        free($2);
        YYERROR;
    }
    | IDENT NEWLINE{
        yyerror("A section name must begin with brackets: [section_name]");
        free($1);
        YYERROR;
    }
  ;

members:
    members member |
    members NEWLINE |

  ;

member:
    IDENT EQUALS value NEWLINE
    {
        free($1);
    }
    | IDENT EQUALS NEWLINE
    {
        yyerror("A configuration entry must contain a value");
        free($1);
        YYERROR;
    }
    | EQUALS value NEWLINE
    {
        yyerror("A configuration entry must contain a key");
        YYERROR;
    }
    | IDENT value NEWLINE
    {
        yyerror("The expected form is: key=value");
        free($1);
        YYERROR;
    }
  ;

value:
    IDENT       { free($1); }
  | STRING       { free($1); }
  | INTEGER
  | DOUBLE
  | BOOLEAN      { free($1); }
  ;

%%

void yyerror(const char *s) {
    printf("Syntax Error at line %d: %s\n", yylineno, s);
}

int main(void) {
    int result = yyparse();
    return result;
}