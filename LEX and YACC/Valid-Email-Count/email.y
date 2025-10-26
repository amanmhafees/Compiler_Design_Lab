%{
#include<stdio.h>
extern FILE *yyin;

int yylex();
void yyerror(char *s);
int count=0;
%}

%token EMAIL

%%
input:

    |input expr
    ;
expr:
    EMAIL {count++;}
%%
void main(){
    yyin=fopen("input.txt","r");
    yyparse();
    printf("Count:%d\n",count);
    fclose(yyin);
}
void yyerror(char *s){
    printf("Error occured: %s",s);
}