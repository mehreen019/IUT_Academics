%{
#include <stdio.h>
#include "validator.tab.h"
%}

%option noyywrap

%%

[ \t\r\n]+          { /* whitespace between tags: ignore */ }

"<html>"    { return HTML_OPEN; }
"</html>"   { return HTML_CLOSE; }
"<head>"    { return HEAD_OPEN; }
"</head>"   { return HEAD_CLOSE; }
"<title>"   { return TITLE_OPEN; }
"</title>"  { return TITLE_CLOSE; }
"<body>"    { return BODY_OPEN; }
"</body>"   { return BODY_CLOSE; }
"<h1>"      { return H1_OPEN; }
"</h1>"     { return H1_CLOSE; }
"<h2>"      { return H2_OPEN; }
"</h2>"     { return H2_CLOSE; }
"<p>"       { return P_OPEN; }
"</p>"      { return P_CLOSE; }
"<div>"     { return DIV_OPEN; }
"</div>"    { return DIV_CLOSE; }
"<b>"       { return B_OPEN; }
"</b>"      { return B_CLOSE; }
"<i>"       { return I_OPEN; }
"</i>"      { return I_CLOSE; }

[^<\n]+     { return TEXT_CONTENT; }

.       { /* unmatched '<' followed by an unknown tag, or stray char: ignore */ }

%%
