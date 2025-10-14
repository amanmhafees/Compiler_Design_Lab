%{
#include<stdio.h>
#include<stdlib.h>
int yylex(void);
int yyerror(char *s);
%}

%token NUMBER
%left '+' '-'
%left '*' '/'

%%
calc:
    expr '\n'{printf("Result=%d\n",$1);}
    ;
expr:
    NUMBER {$$=$1;}
    | expr '+' expr {$$=$1+$3;}
    | expr '-' expr {$$=$1-$3;}
    | expr '*' expr {$$=$1*$3;}
    | expr '/' expr {
                if($3==0){
                    yyerror("Divisionby zero");
                    $$=0;
                }
                else{
                    $$=$1/$3;
                }
            }
    ;
%%
int yyerror(char *msg) {
 printf("Error: %s\n", msg);
 return 0;
 }
 int main() {
 printf("Enter an expression (with +,-, *, /):\n");
 yyparse();
 return 0;
 }