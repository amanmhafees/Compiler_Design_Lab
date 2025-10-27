%{
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
extern FILE *yyin;
int yylex();
void yyerror(char*s);
%}
%token SMALL CAPITAL

%%
input:
    |input ch
    ;
ch:
    SMALL {putchar(toupper($1));}
    |CAPITAL {putchar(tolower($1));}
    ;
%%
int main() {
    yyin = fopen("input.txt", "r");
    if (!yyin) {
        printf("Error: cannot open input file.\n");
        return 1;
    }

    yyparse();
    fclose(yyin);
    return 0;
}

void yyerror(char *s) {
    printf("Error: %s\n", s);
}