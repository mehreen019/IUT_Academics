%{
    #include <stdio.h>
    int keywords=0, identifiers=0, int_const=0, float_const=0;
    int char_const=0, str_const=0;
    int arith=0, relat=0, logic=0, bitwise=0, assign=0, incdec=0;
    int delimiters=0;

    FILE *out;
%}

%%

[ \t\n]+                        ;
"//"[^\n]*                      ;
"/*"([^*]|\*+[^*/])*\*+"/"      ;

"int"|"float"|"if"|"else"|"print"   { fprintf(out, "<%s, KEYWORD>\n", yytext); keywords++; }

"++"                            { fprintf(out, "<%s, INCDEC_OP>\n", yytext); incdec++; }
"--"                            { fprintf(out, "<%s, INCDEC_OP>\n", yytext); incdec++; }

"&&"|"||"|"!"                   { fprintf(out, "<%s, LOGICAL_OP>\n", yytext); logic++; }

"=="|"!="|"<="|">="|"<"|">"     { fprintf(out, "<%s, RELATIONAL_OP>\n", yytext); relat++; }

"+="|"-="|"*="|"/="|"%="|"="   { fprintf(out, "<%s, ASSIGNMENT_OP>\n", yytext); assign++; }

"+"|"-"|"*"|"/"|"%"             { fprintf(out, "<%s, ARITHMETIC_OP>\n", yytext); arith++; }

"<<"|">>"|"&"|"|"|"^"|"~"       { fprintf(out, "<%s, BITWISE_OP>\n", yytext); bitwise++; }

";"|","|"("|")"|"{"|"}"         { fprintf(out, "<%s, DELIMITER>\n", yytext); delimiters++; }

[0-9]+\.[0-9]+                  { fprintf(out, "<%s, FLOAT_CONST>\n", yytext); float_const++; }
[0-9]+                          { fprintf(out, "<%s, INT_CONST>\n", yytext); int_const++; }
\'([^'\\]|\\.)\'                { fprintf(out, "<%s, CHAR_CONST>\n", yytext); char_const++; }
\"([^"\\]|\\.)*\"               { fprintf(out, "<%s, STRING_CONST>\n", yytext); str_const++; }

[a-zA-Z_][a-zA-Z0-9_]*         { fprintf(out, "<%s, IDENTIFIER>\n", yytext); identifiers++; }

.                               { fprintf(out, "<%s, UNKNOWN>\n", yytext); }

%%

int yywrap() { return 1; }

int main() {
    yyin = fopen("input.txt", "r");
    out  = fopen("output.txt", "w");

    yylex();

    int constants = int_const + float_const + char_const + str_const;
    int operators = arith + relat + logic + bitwise + assign + incdec;
    int total = keywords + identifiers + constants + operators + delimiters;

    fprintf(out, "\nTotal Tokens: %d\n", total);
    fprintf(out, "Keywords: %d\n", keywords);
    fprintf(out, "Identifiers: %d\n", identifiers);
    fprintf(out, "Constants: %d\n", constants);
    fprintf(out, "  Integer Constants: %d\n", int_const);
    fprintf(out, "  Float Constants: %d\n", float_const);
    fprintf(out, "  Character Constants: %d\n", char_const);
    fprintf(out, "  String Constants: %d\n", str_const);
    fprintf(out, "Operators: %d\n", operators);
    fprintf(out, "  Arithmetic: %d\n", arith);
    fprintf(out, "  Relational: %d\n", relat);
    fprintf(out, "  Logical: %d\n", logic);
    fprintf(out, "  Bitwise: %d\n", bitwise);
    fprintf(out, "  Assignment: %d\n", assign);
    fprintf(out, "  Increment/Decrement: %d\n", incdec);
    fprintf(out, "Delimiters: %d\n", delimiters);

    fclose(yyin);
    fclose(out);
    return 0;
}
