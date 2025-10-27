%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(char *s);
%}

%union {
    int num;
}

%token <num> NUMBER
%type  <num> expr

%left '+' '-'
%left '*' '/'
%left '(' ')'

%%

calc:
    expr '\n' { printf("Result = %d\n", $1); }
    ;

expr:
      NUMBER          { $$ = $1; }
    | expr '+' expr   { $$ = $1 + $3; }
    | expr '-' expr   { $$ = $1 - $3; }
    | expr '*' expr   { $$ = $1 * $3; }
    | expr '/' expr   {
        if ($3 == 0) {
            yyerror("Division by zero");
            $$ = 0;
        } else {
            $$ = $1 / $3;
        }
      }
    | '(' expr ')'    { $$ = $2; }
    ;

%%

int main() {
    printf("Enter the expression:\n");
    yyparse();
    return 0;
}

void yyerror(char *s) {
    printf("Error: %s\n", s);
}
