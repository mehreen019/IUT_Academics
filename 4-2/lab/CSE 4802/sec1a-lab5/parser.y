%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yylex(void);
void yyerror(const char *s);

#define MAX_KEYS 1024
static char *seen_keys[MAX_KEYS];
static int total_keys = 0;

static int key_exists(const char *key) {
    int i;
    for (i = 0; i < total_keys; i++) {
        if (strcmp(seen_keys[i], key) == 0) {
            return 1;
        }
    }
    return 0;
}

static void check_key(char *key) {
    if (key_exists(key)) {
        printf("Semantic Error: Duplicate key %s\n", key);
    } else {
        if (total_keys >= MAX_KEYS) {
            fprintf(stderr, "Error: too many keys (max %d)\n", MAX_KEYS);
            exit(1);
        }
        seen_keys[total_keys] = strdup(key);
        total_keys++;
    }
}

static void free_keys(void) {
    int i;
    for (i = 0; i < total_keys; i++) {
        free(seen_keys[i]);
    }
}
%}

%union {
    double dval;
    char *str;
}

%token <str> STRING
%token <dval> INTEGER DOUBLE
%token TRUE FALSE NULL_VALUE
%token LEFT_BRACE RIGHT_BRACE LEFT_BRACKET RIGHT_BRACKET COLON COMMA

%%

json:
    value
    {
        int i;
        printf("JSON document is valid.\n");
        printf("\nTotal Keys: %d\n", total_keys);
        printf("Keys found:\n");
        for (i = 0; i < total_keys; i++) {
            printf("  %s\n", seen_keys[i]);
        }
    }
  ;

value:
    object
  | array
  | STRING       { free($1); }
  | INTEGER
  | DOUBLE
  | TRUE
  | FALSE
  | NULL_VALUE
  ;

object:
    LEFT_BRACE RIGHT_BRACE
  | LEFT_BRACE members RIGHT_BRACE
  ;

members:
    member
  | members COMMA member
  ;

member:
    STRING COLON value
    {
        check_key($1);
        free($1);
    }
  ;

array:
    LEFT_BRACKET RIGHT_BRACKET
  | LEFT_BRACKET elements RIGHT_BRACKET
  ;

elements:
    value
  | elements COMMA value
  ;

%%

void yyerror(const char *s) {
    printf("Syntax Error: %s\n", s);
}

int main(void) {
    int result = yyparse();
    free_keys();
    return result;
}