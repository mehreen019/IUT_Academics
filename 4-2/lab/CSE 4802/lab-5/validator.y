%{
#include <stdio.h>
#include <string.h>

int yylex(void);
void yyerror(const char *s);

/* Section 13 of the assignment lists "ensure only one <html>/<head>/
   <body>" as an optional semantic check. Under the grammar as given
   (section 9), html_document already has exactly one head_section
   slot and exactly one body_section slot, so a duplicate <head> or
   <body> is rejected by the grammar itself as a SYNTAX error before
   any semantic action would run -- there's no path left over for a
   semantic duplicate check to catch. This validator therefore relies
   on the grammar for that guarantee, which the assignment explicitly
   says is fine (section 12: "these constraints are directly enforced
   by the grammar"). semanticError() is kept below, ready to call from
   a new grammar rule if you extend this (e.g. section 18's list/table
   extensions) in a way that makes a real semantic check reachable. */
int semanticErrorFound = 0;

void semanticError(const char *msg) {
    semanticErrorFound = 1;
    printf("Semantic Error:\n%s\n", msg);
}
%}

%token HTML_OPEN HTML_CLOSE
%token HEAD_OPEN HEAD_CLOSE
%token TITLE_OPEN TITLE_CLOSE
%token BODY_OPEN BODY_CLOSE
%token H1_OPEN H1_CLOSE
%token H2_OPEN H2_CLOSE
%token P_OPEN P_CLOSE
%token DIV_OPEN DIV_CLOSE
%token B_OPEN B_CLOSE
%token I_OPEN I_CLOSE
%token TEXT_CONTENT

%%

document:
    html_document
        {
            if (!semanticErrorFound)
                printf("HTML document is structurally valid.\n");
        }
    ;

html_document:
    HTML_OPEN
    head_section
    body_section
    HTML_CLOSE
    ;

head_section:
    HEAD_OPEN
    title_section
    HEAD_CLOSE
    ;

title_section:
    TITLE_OPEN TEXT_CONTENT TITLE_CLOSE
    | TITLE_OPEN TITLE_CLOSE
    ;

body_section:
    BODY_OPEN
    content
    BODY_CLOSE
    ;

content:
    content content_item
    | /* empty */
    ;

content_item:
    TEXT_CONTENT
    | heading
    | paragraph
    | div
    | bold
    | italic
    ;

heading:
    H1_OPEN content H1_CLOSE
    | H2_OPEN content H2_CLOSE
    ;

paragraph:
    P_OPEN content P_CLOSE
    ;

div:
    DIV_OPEN content DIV_CLOSE
    ;

bold:
    B_OPEN content B_CLOSE
    ;

italic:
    I_OPEN content I_CLOSE
    ;

%%

void yyerror(const char *s) {
    printf("Syntax Error:\n%s.\n", s);
}

int main(void) {
    yyparse();
    return 0;
}
