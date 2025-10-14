%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "y.tab.h"
%}

%%

[0-9]+          { yylval = atoi(yytext); return NUMBER; }
[+\-*/\n]       { return yytext[0]; }    /* Return operators and newline */
[ \t]           ;                        /* Ignore spaces and tabs */
.               { printf("Invalid character: %s\n", yytext); }

%%

int yywrap() {
    return 1;
}
