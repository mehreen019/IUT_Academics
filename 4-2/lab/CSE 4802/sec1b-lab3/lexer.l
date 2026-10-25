%{
#include "parser.tab.h"
#include <stdlib.h>
#include <string.h>
%}

%%

[a-zA-Z][a-zA-Z0-9_]*   { yylval.sval = strdup(yytext); return ID; }

[ \t]       ;
\n          return '\n';

"+"         return '+';
"-"         return '-';
"*"         return '*';
"/"         return '/';
"^"         return '^';
"("         return '(';
")"         return ')';

.           return yytext[0];

%%

int yywrap() {
    return 1;
}