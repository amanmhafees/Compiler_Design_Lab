%{
    #include "y.tab.h"
    #include <stdlib.h>
    #include <string.h>
    void yyerror(char *s);  // <-- Declare before use
%}

%%
[_a-zA-Z][a-zA-Z0-9_]*    { return ID; }               /* Valid identifier */
.                         { yyerror("Invalid"); }      /* Anything else */
[\t\n]+                   ;                            /* Ignore spaces/tabs */
%%

int yywrap() {
    return 1;
}
