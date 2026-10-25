%{
#include "parser.tab.h"
#include <stdlib.h>
#include <string.h>
%}

%%

\xEF\xBB\xBF               ;

\"[^\"]*\"                { yylval.str = strdup(yytext + 1); yylval.str[strlen(yylval.str) - 1] = '\0'; return STRING; }
-?[0-9]+\.[0-9]+           { yylval.dval = atof(yytext); return DOUBLE; }
-?[0-9]+                   { yylval.dval = atof(yytext); return INTEGER; }

"true"      return TRUE;
"false"     return FALSE;
"null"      return NULL_VALUE;

"{"         return LEFT_BRACE;
"}"         return RIGHT_BRACE;
"["         return LEFT_BRACKET;
"]"         return RIGHT_BRACKET;
":"         return COLON;
","         return COMMA;

[ \t\n\r]   ;

.           { return yytext[0]; }

%%

int yywrap(void) { return 1; }