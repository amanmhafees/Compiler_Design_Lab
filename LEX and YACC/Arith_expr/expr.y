%{
    #include <stdio.h>
    #include <stdlib.h>
    void yyerror(char *s);
    int yylex(void);
%}
%union{
    int num
}

%token <num> DIGIT 
%token LETTER
%left '+' '-'
%left '*' '/'
%right UMINUS

%%
input:
    expr { printf("Valid Arithmetic Expression\n"); exit(0); }
;

expr:
      expr '+' expr       { /* addition */ }
    | expr '-' expr       { /* subtraction */ }
    | expr '*' expr       { /* multiplication */ }
    | expr '/' expr       { /* division */ }
    | '-' expr %prec UMINUS { /* unary minus */ }
    | '(' expr ')'        { /* parenthesis */ }
    | LETTER              { /* identifier */ }
    | DIGIT               { /* number */ }
;
%%

int main() {
    printf("Enter the expression:\n");
    yyparse();
    printf("Parsing completed\n");
    return 0;
}

void yyerror(char *msg) {
    printf("Invalid Arithmetic Expression\n");
    exit(1);
}
