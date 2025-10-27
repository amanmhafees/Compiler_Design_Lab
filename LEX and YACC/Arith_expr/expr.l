%{
    #include "y.tab.h"   // for token definitions
    #include <stdlib.h>
    #include <string.h>
%}

%%
[0-9]+                    { yylval.num = atoi(yytext); return DIGIT; }
[_a-zA-Z][_a-zA-Z0-9]*    { return LETTER; }

"+"    { return '+'; }
"-"    { return '-'; }
"*"    { return '*'; }
"/"    { return '/'; }
"("    { return '('; }
")"    { return ')'; }

[ \t]+   ;   // ignore spaces and tabs
\n       { return 0; }
.        { return yytext[0]; }
%%

int yywrap() {
    return 1;
}
