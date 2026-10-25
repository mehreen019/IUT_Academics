%{
    int wc=0, nc=0, oc=0;
}

%%

[\t]+ ;
[a-zA-Z]+ {print("%s :word\n", yytext); wc++;}
[+-]?([0-9]*[.])?[0-9]+ {print("%s :number\n", yytext); nc++;}
. {print("%s :unknown\n", yytext); oc++;}

%%

int main() {
    printf("Enter a string: ");
    yylex();
    printf("Words: %d\n", wc);
    printf("Numbers: %d\n", nc);
    printf("Unknown: %d\n", oc);
    return 0;
}