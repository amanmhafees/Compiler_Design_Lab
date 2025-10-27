%{
#include<stdio.h>
#include "y.tab.h"
extern FILE*yyin;
%}
%%
[a-z] {yylval=yytext[0]; return SMALL;}
[A-Z] {yylval=yytext[0]; return CAPITAL;}
.|\n {putchar(yytext[0]);}
%%
int yywrap(){
    return 1;
}