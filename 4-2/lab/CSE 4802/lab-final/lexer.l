%{
#include <stdio.h>
#include "parser.tab.h"
#include <stdlib.h>
#include <string.h>

extern int yylineno;
%}

%option yylineno

%%

[ \t\r]+                   ;
\n                         { return NEWLINE; }

[0-9]+(\.[0-9]+){3}        { yylval.str = strdup(yytext); return STRING; }
-?[0-9]+\.[0-9]+           { yylval.dval = atof(yytext); return DOUBLE; }
-?[0-9]+                   { yylval.dval = atof(yytext); return INTEGER; }
[A-Za-z_][A-Za-z0-9_]*     { yylval.str = strdup(yytext); return IDENT; }

"true"|"false"     { yylval.str = strdup(yytext); return BOOLEAN; }

"["         return LEFT_BRACKET;
"]"         return RIGHT_BRACKET;
"="         return EQUALS;

.           { return yytext[0]; }

%%

int yywrap(void) { return 1; }