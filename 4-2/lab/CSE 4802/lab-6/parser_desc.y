/*
 * parser.y
 * -----------------------------------------------------------------------
 * YACC grammar + Syntax-Directed Definition (SDD) for Assignment S2-6.
 *
 * Grammar implemented (as given in the assignment, Section 6):
 *
 *   Program   -> StmtList
 *   StmtList  -> StmtList Stmt | Stmt
 *   Stmt      -> id '=' Expr ';'
 *   Expr      -> Expr '+' Term | Expr '-' Term | Term
 *   Term      -> Term '*' Factor | Term '/' Factor | Term '%' Factor | Factor
 *   Factor    -> '(' Expr ')' | id | number
 *
 * Every non-terminal that represents a value (Expr, Term, Factor) carries
 * a synthesized string attribute called `place`, exactly as described in
 * Section 7 of the handout: place holds the name of the location (an
 * identifier, a constant, or a temporary Tn) where the computed value of
 * that subexpression lives.
 *
 * Semantic actions call:
 *   - newTemp()        to synthesize a fresh temporary name "T1", "T2", ...
 *   - emit(op,a,b,c)   to print one line of Pseudo Assembly Code (PAC)
 *
 * Operator precedence/associativity is NOT relied upon from %left/%right
 * declarations alone for correctness -- the grammar itself is already
 * layered (Expr/Term/Factor) so precedence and left-associativity fall
 * out of the grammar structure, matching the handout exactly. %left
 * declarations are still included as good practice / to resolve the
 * dangling ambiguity that does not otherwise exist in this grammar, and
 * they cost nothing here since the grammar is already unambiguous.
 * -----------------------------------------------------------------------
 */

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yylex(void);
void yyerror(const char *s);
extern int yylineno;
extern FILE *yyin;

/* ---- SDD helper state -------------------------------------------- */

static int tempCount = 0;   /* counter used by newTemp() */

/* newTemp(): synthesizes a fresh temporary variable name "T1", "T2", ...
 * Returns a heap-allocated string owned by the caller (freed by whoever
 * uses it up in an emit(), consistent with how ID/NUMBER strings from
 * the lexer are also heap-allocated via strdup). */
char *newTemp(void) {
    char buf[32];
    tempCount++;
    snprintf(buf, sizeof(buf), "T%d", tempCount);
    return strdup(buf);
}

/* emit(): prints one line of Pseudo Assembly Code.
 *
 * Two forms are used in this program:
 *   emit3(op, dest, src1, src2)  ->  "OP dest, src1, src2"   (ADD/SUB/MUL/DIV/MOD)
 *   emit2(op, dest, src1)        ->  "OP dest, src1"          (MOV)
 *
 * Kept as two small functions (rather than one variadic emit) so each
 * call site matches the exact instruction shapes shown in Section 8/
 * Appendix A of the handout: MOV takes 2 operands, arithmetic ops take 3.
 */
static void emit3(const char *op, const char *dest, const char *src1, const char *src2) {
    printf("%s %s, %s, %s\n", op, dest, src1, src2);
}

static void emit2(const char *op, const char *dest, const char *src1) {
    printf("%s %s, %s\n", op, dest, src1);
}

/* Track whether a syntax error occurred, so main() can set the process
 * exit code appropriately (Student Task 7: syntax error reporting). */
int hadError = 0;

%}

/* ---------------------------------------------------------------------
 * Semantic value type.
 * Every token that carries text (ID, NUMBER) and every non-terminal that
 * carries a `place` attribute (Expr, Term, Factor) uses the `str` member.
 * ------------------------------------------------------------------- */
%union {
    char *str;
}

%token <str> ID
%token <str> NUMBER
%token PLUS MINUS TIMES DIVIDE MOD
%token ASSIGN SEMI LPAREN RPAREN

%type <str> Expr Term Factor

/* Precedence, lowest to highest (not strictly required given the
 * layered grammar, but documents intent and silences any residual
 * ambiguity warnings). */
%left PLUS MINUS
%left TIMES DIVIDE MOD

%%

/* ---------------------------------------------------------------------
 * Program -> StmtList
 * ------------------------------------------------------------------- */
Program
    : StmtList
        {
            /* Whole program reduced; nothing further to emit here since
               each Stmt already emitted its own instructions. */
        }
    ;

/* ---------------------------------------------------------------------
 * StmtList -> StmtList Stmt | Stmt
 * ------------------------------------------------------------------- */
StmtList
    : StmtList Stmt
    | Stmt
    ;

/* ---------------------------------------------------------------------
 * Stmt -> id '=' Expr ';'
 *
 * SDD:
 *   emit( MOV id, Expr.place )
 * ------------------------------------------------------------------- */
Stmt
    : ID ASSIGN Expr SEMI
        {
            emit2("MOV", $1, $3);
            free($1);
            free($3);
        }
    | error SEMI
        {
            /* Syntax error recovery: resynchronize at the next ';' so
               the parser can continue checking the rest of the input
               instead of aborting on the first bad statement. */
            fprintf(stderr, "Syntax error: skipping malformed statement (line %d)\n", yylineno);
            hadError = 1;
            yyerrok;
        }
    ;

/* ---------------------------------------------------------------------
 * Expr -> Expr '+' Term | Expr '-' Term | Term
 *
 * SDD (mirrors Section 7 example exactly for '+'; '-' is symmetric):
 *   Expr.place = newTemp()
 *   emit( ADD Expr.place, Expr1.place, Term.place )
 * ------------------------------------------------------------------- */
Expr
    : Expr PLUS Term
        {
            $$ = newTemp();
            emit3("ADD", $$, $1, $3);
            free($1);
            free($3);
        }
    | Expr MINUS Term
        {
            $$ = newTemp();
            emit3("SUB", $$, $1, $3);
            free($1);
            free($3);
        }
    | Term
        {
            $$ = $1;
        }
    ;

/* ---------------------------------------------------------------------
 * Term -> Term '*' Factor | Term '/' Factor | Term '%' Factor | Factor
 *
 * SDD is analogous to Expr's, using MUL / DIV / MOD respectively.
 * ------------------------------------------------------------------- */
Term
    : Term TIMES Factor
        {
            $$ = newTemp();
            emit3("MUL", $$, $1, $3);
            free($1);
            free($3);
        }
    | Term DIVIDE Factor
        {
            $$ = newTemp();
            emit3("DIV", $$, $1, $3);
            free($1);
            free($3);
        }
    | Term MOD Factor
        {
            $$ = newTemp();
            emit3("MOD", $$, $1, $3);
            free($1);
            free($3);
        }
    | Factor
        {
            $$ = $1;
        }
    ;

/* ---------------------------------------------------------------------
 * Factor -> '(' Expr ')' | id | number
 *
 * No new temporary or emit for these cases: a parenthesized expression's
 * place is simply the inner expression's place, and identifiers/numbers
 * are already valid PAC operands as-is.
 * ------------------------------------------------------------------- */
Factor
    : LPAREN Expr RPAREN
        {
            $$ = $2;
        }
    | ID
        {
            $$ = $1;
        }
    | NUMBER
        {
            $$ = $1;
        }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Syntax error at line %d: %s\n", yylineno, s);
    hadError = 1;
}

int main(int argc, char **argv) {
    if (argc > 1) {
        FILE *f = fopen(argv[1], "r");
        if (!f) {
            fprintf(stderr, "Error: could not open input file '%s'\n", argv[1]);
            return 1;
        }
        yyin = f;
    }
    /* If no filename is given, yyin defaults to stdin. */

    yyparse();

    if (argc > 1) {
        fclose(yyin);
    }

    return hadError ? 1 : 0;
}
