%{
#include "parser.tab.h"
#include <stdlib.h>
#include <string.h>
%}

%%

[0-9]+\.[0-9]+ {
    yylval.dval = atof(yytext);
    return DOUBLE;
}

[0-9]+ {
    yylval.dval = (double)atoi(yytext);
    return INTEGER;
}

"sin"   { return SIN; }
"cos"   { return COS; }
"tan"   { return TAN; }
"sqrt"  { return SQRT; }
"log"   { return LOG; }

[a-zA-Z_][a-zA-Z0-9_]* {
    yylval.sval = strdup(yytext);
    return ID;
}

[ \t]   { ; }
\n      { return '\n'; }
"+"     { return '+'; }
"-"     { return '-'; }
"*"     { return '*'; }
"/"     { return '/'; }
"^"     { return '^'; }
"("     { return '('; }
")"     { return ')'; }
"="     { return '='; }
.       { return yytext[0]; }

%%

int yywrap() {
    return 1;
}