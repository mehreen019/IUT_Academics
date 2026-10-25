/*
 * lexer.l
 * -----------------------------------------------------------------------
 * Lexical analyzer for Assignment S2-6.
 *
 * Recognizes tokens for:
 *   - identifiers            (ID)
 *   - integer constants       (NUMBER)
 *   - assignment operator '='
 *   - arithmetic operators   + - * / %
 *   - parentheses            ( )
 *   - statement terminator   ;
 *   - whitespace / comments  (skipped)
 *
 * Each ID / NUMBER token also populates yylval.str (declared in the
 * parser's union) so the parser can carry the actual text of the
 * identifier or constant, which is needed when emitting PAC operands
 * such as "MOV a, T1".
 * -----------------------------------------------------------------------
 */

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
                        /* identifier: copy text into yylval.str */
                        yylval.str = strdup(yytext);
                        return ID;
                    }

{DIGIT}+            {
                        /* integer constant: copy text into yylval.str */
                        yylval.str = strdup(yytext);
                        return NUMBER;
                    }

[ \t\r]+            { /* skip whitespace */ }

\n                  { /* newline: yylineno auto-increments, nothing else to do */ }

"//".*              { /* skip single-line comments */ }

.                   {
                        fprintf(stderr,
                            "Lexical error at line %d: unexpected character '%s'\n",
                            yylineno, yytext);
                    }

%%
