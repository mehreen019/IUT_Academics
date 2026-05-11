%{
#include <stdio.h>
#include <string.h>

FILE *output;

/* Counters */
int total_tokens = 0;
int count_keywords = 0;
int count_identifiers = 0;
int count_int_const = 0;
int count_float_const = 0;
int count_char_const = 0;
int count_string_const = 0;
int count_arith_op = 0;
int count_relat_op = 0;
int count_logic_op = 0;
int count_bitwise_op = 0;
int count_assign_op = 0;
int count_incdec_op = 0;
int count_delimiters = 0;

void print_token(const char *type, const char *lexeme) {
    fprintf(output, "<%s, %s>\n", type, lexeme);
    total_tokens++;
}
%}

%option noyywrap
%option yylineno

/* Definitions */
DIGIT       [0-9]
LETTER      [a-zA-Z_]
ALPHANUM    [a-zA-Z0-9_]

INT_CONST   {DIGIT}+
FLOAT_CONST {DIGIT}+"."{DIGIT}+
CHAR_CONST  '([^'\\]|\\.)'
STR_CONST   \"([^"\\]|\\.)*\"
IDENTIFIER  {LETTER}{ALPHANUM}*

%%

 /* ---------- KEYWORDS ---------- */
"int"       { print_token("KEYWORD", yytext); count_keywords++; }
"float"     { print_token("KEYWORD", yytext); count_keywords++; }
"if"        { print_token("KEYWORD", yytext); count_keywords++; }
"else"      { print_token("KEYWORD", yytext); count_keywords++; }
"print"     { print_token("KEYWORD", yytext); count_keywords++; }

 /* ---------- INCREMENT / DECREMENT (must come before arithmetic) ---------- */
"++"        { print_token("INCREMENT_DECREMENT_OP", yytext); count_incdec_op++; }
"--"        { print_token("INCREMENT_DECREMENT_OP", yytext); count_incdec_op++; }

 /* ---------- LOGICAL OPERATORS (must come before relational/bitwise) ---------- */
"&&"        { print_token("LOGICAL_OP", yytext); count_logic_op++; }
"||"        { print_token("LOGICAL_OP", yytext); count_logic_op++; }
"!"         { print_token("LOGICAL_OP", yytext); count_logic_op++; }

 /* ---------- RELATIONAL OPERATORS ---------- */
"=="        { print_token("RELATIONAL_OP", yytext); count_relat_op++; }
"!="        { print_token("RELATIONAL_OP", yytext); count_relat_op++; }
"<="        { print_token("RELATIONAL_OP", yytext); count_relat_op++; }
">="        { print_token("RELATIONAL_OP", yytext); count_relat_op++; }
"<"         { print_token("RELATIONAL_OP", yytext); count_relat_op++; }
">"         { print_token("RELATIONAL_OP", yytext); count_relat_op++; }

 /* ---------- ASSIGNMENT OPERATORS (must come before arithmetic =) ---------- */
"+="        { print_token("ASSIGNMENT_OP", yytext); count_assign_op++; }
"-="        { print_token("ASSIGNMENT_OP", yytext); count_assign_op++; }
"*="        { print_token("ASSIGNMENT_OP", yytext); count_assign_op++; }
"/="        { print_token("ASSIGNMENT_OP", yytext); count_assign_op++; }
"%="        { print_token("ASSIGNMENT_OP", yytext); count_assign_op++; }
"="         { print_token("ASSIGNMENT_OP", yytext); count_assign_op++; }

 /* ---------- ARITHMETIC OPERATORS ---------- */
"+"         { print_token("ARITHMETIC_OP", yytext); count_arith_op++; }
"-"         { print_token("ARITHMETIC_OP", yytext); count_arith_op++; }
"*"         { print_token("ARITHMETIC_OP", yytext); count_arith_op++; }
"/"         { print_token("ARITHMETIC_OP", yytext); count_arith_op++; }
"%"         { print_token("ARITHMETIC_OP", yytext); count_arith_op++; }

 /* ---------- BITWISE OPERATORS ---------- */
"&"         { print_token("BITWISE_OP", yytext); count_bitwise_op++; }
"|"         { print_token("BITWISE_OP", yytext); count_bitwise_op++; }
"^"         { print_token("BITWISE_OP", yytext); count_bitwise_op++; }
"~"         { print_token("BITWISE_OP", yytext); count_bitwise_op++; }
"<<"        { print_token("BITWISE_OP", yytext); count_bitwise_op++; }
">>"        { print_token("BITWISE_OP", yytext); count_bitwise_op++; }

 /* ---------- DELIMITERS ---------- */
";"         { print_token("DELIMITER", yytext); count_delimiters++; }
","         { print_token("DELIMITER", yytext); count_delimiters++; }
"("         { print_token("DELIMITER", yytext); count_delimiters++; }
")"         { print_token("DELIMITER", yytext); count_delimiters++; }
"{"         { print_token("DELIMITER", yytext); count_delimiters++; }
"}"         { print_token("DELIMITER", yytext); count_delimiters++; }

 /* ---------- CONSTANTS (float before int to avoid prefix match) ---------- */
{FLOAT_CONST}   { print_token("FLOAT_CONST", yytext); count_float_const++; }
{INT_CONST}     { print_token("INT_CONST", yytext);   count_int_const++;   }
{CHAR_CONST}    { print_token("CHAR_CONST", yytext);  count_char_const++;  }
{STR_CONST}     { print_token("STRING_CONST", yytext); count_string_const++; }

 /* ---------- IDENTIFIERS (after keywords) ---------- */
{IDENTIFIER}    { print_token("IDENTIFIER", yytext); count_identifiers++; }

 /* ---------- IGNORE whitespace and newlines ---------- */
[ \t\r\n]+  { /* skip */ }

 /* ---------- IGNORE single-line comments ---------- */
"//"[^\n]*  { /* skip */ }

 /* ---------- IGNORE multi-line comments ---------- */
"/*"([^*]|\*+[^*/])*\*+"/"  { /* skip */ }

 /* ---------- UNKNOWN characters ---------- */
.           { fprintf(output, "<UNKNOWN, %s>\n", yytext); total_tokens++; }

%%

int main() {
    FILE *input = fopen("input.txt", "r");
    if (!input) {
        printf("Error: Cannot open input.txt\n");
        return 1;
    }

    output = fopen("output.txt", "w");
    if (!output) {
        printf("Error: Cannot open output.txt\n");
        fclose(input);
        return 1;
    }

    fprintf(output, "Token Stream:\n");
    fprintf(output, "=============\n");

    yyin = input;
    yylex();

    /* Derived totals */
    int count_constants = count_int_const + count_float_const
                        + count_char_const + count_string_const;
    int count_operators = count_arith_op + count_relat_op + count_logic_op
                        + count_bitwise_op + count_assign_op + count_incdec_op;

    /* Summary */
    fprintf(output, "\nSummary Section:\n");
    fprintf(output, "================\n");
    fprintf(output, "Total Tokens:                 %d\n", total_tokens);
    fprintf(output, "Keywords:                     %d\n", count_keywords);
    fprintf(output, "Identifiers:                  %d\n", count_identifiers);
    fprintf(output, "Constants:                    %d\n", count_constants);
    fprintf(output, "  Integer Constants:          %d\n", count_int_const);
    fprintf(output, "  Float Constants:            %d\n", count_float_const);
    fprintf(output, "  Character Constants:        %d\n", count_char_const);
    fprintf(output, "  String Constants:           %d\n", count_string_const);
    fprintf(output, "Operators:                    %d\n", count_operators);
    fprintf(output, "  Arithmetic Operators:       %d\n", count_arith_op);
    fprintf(output, "  Relational Operators:       %d\n", count_relat_op);
    fprintf(output, "  Logical Operators:          %d\n", count_logic_op);
    fprintf(output, "  Bitwise Operators:          %d\n", count_bitwise_op);
    fprintf(output, "  Assignment Operators:       %d\n", count_assign_op);
    fprintf(output, "  Increment/Decrement Ops:    %d\n", count_incdec_op);
    fprintf(output, "Delimiters:                   %d\n", count_delimiters);

    fclose(input);
    fclose(output);

    printf("Done! Output written to output.txt\n");
    return 0;
}
