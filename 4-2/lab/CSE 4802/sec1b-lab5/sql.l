%{
#include <string.h>
#include "y.tab.h"
%}
%%
[Ss][Ee][Ll][Ee][Cc][Tt]   { return SELECT; }
[Ff][Rr][Oo][Mm]           { return FROM;   }
[Ww][Hh][Ee][Rr][Ee]       { return WHERE;  }
[Oo][Rr][Dd][Ee][Rr]       { return ORDER;  }
[Bb][Yy]                   { return BY;     }
[Aa][Nn][Dd]               { return AND;    }
[Oo][Rr]                   { return OR;     }

"<="|">="|"<>"|"="|"<"|">" { return RELOP; }
"*"                        { return STAR;      }
","                        { return COMMA;     }
";"                        { return SEMICOLON; }

[0-9]+"."[0-9]+            { return DOUBLE_LITERAL;  }
[0-9]+                     { return INTEGER_LITERAL; }
'[^']*'                    { return STRING_LITERAL;  }

[A-Za-z_][A-Za-z0-9_]*     { yylval.str = strdup(yytext); return IDENTIFIER; }

[ \t\r\n]+                 { }
.                          { return yytext[0]; }
%%
int yywrap(void) { return 1; }
