%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.tab.h"

extern int yylineno;
%}

%option yylineno
%option noyywrap

DIGIT     [0-9]
LETTER    [A-Za-z_]

%%

"+"                 { return PLUS;   }
"-"                 { return MINUS;  }
"*"                 { return TIMES;  }
"/"                 { return DIVIDE; }
"%"                 { return MOD;    }
"="                 { return ASSIGN; }
";"                 { return SEMI;   }
"("                 { return LPAREN; }
")"                 { return RPAREN; }

{LETTER}({LETTER}|{DIGIT})*   {
                        yylval.str = strdup(yytext);
                        return ID;
                    }

{DIGIT}+            {
                        yylval.str = strdup(yytext);
                        return NUMBER;
                    }

[ \t\r]+            { /* skip whitespace */ }

\n                  { /* newline */ }

"//".*              { /* skip single-line comments */ }

.                   {
                        fprintf(stderr,
                            "Lexical error at line %d: unexpected character '%s'\n",
                            yylineno, yytext);
                    }

%%
