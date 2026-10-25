%{
#include "parser.tab.h"
#include <stdlib.h> 
%}

%%

[0-9]+(\.[0-9]+)? {
    yylval.dval = atof(yytext);
    return NUMBER;
}

[ \t]   ;

\n  return '\n';

"+"  return '+';
"-"  return '-';

"sin"   return SIN;
"cos"   return COS;
"tan"   return TAN;

"sqrt"  return SQRT;

"log"   return LOG;

"*"  return '*';

"/"  return '/';

"^"  return '^';

"("  return '(';
")"  return ')';

.   return yytext[0];

%%

int yywrap()
{
    return 1;
}