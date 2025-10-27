%{
#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"   // <--- must include this after running yacc -d
%}

%%
[0-9]+      { yylval.num = atoi(yytext); return NUMBER; }
[+\-*/()\n] { return yytext[0]; }
[ \t]       ;   /* ignore spaces */
.           { printf("Invalid character: %s\n", yytext); }
%%

int yywrap() { return 1; }
