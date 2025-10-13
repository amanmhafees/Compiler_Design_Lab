%{
#include<stdio.h>
%}
%%
[0-9]*[02468] {printf("Even number\n",yytext);}
[0-9]*[13579] {printf("Odd number\n",yytext);}
%%
int main(){
    printf("Enter a number and press Ctrl+D when done:\n");
    yylex();
    return 0;
}
int yywrap(){
    return 1;
}
