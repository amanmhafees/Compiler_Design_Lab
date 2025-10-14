%{
    #include<stdio.h>
    #include<string.h>
    #include "y.tab.h"
    extern FILE *yyin;
    extern FILE *valid_out;
    extern FILE *invalid_out;
%}

%%
[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,4} {
    yylval.str = strdup(yytext);
    return VALID_EMAIL;
}

[^ \t\n]+ {
    yylval.str = strdup(yytext);
    return INVALID_EMAIL;
}

[\t\n,]+   ;
%%

int yywrap() {
    return 1;
}
