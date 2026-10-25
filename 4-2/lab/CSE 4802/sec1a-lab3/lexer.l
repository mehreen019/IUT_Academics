%{
#include "y.tab.h"
#include <stdlib.h>
%}

%%

[0-9]+      { yylval = atoi(yytext); return NUMBER; }
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