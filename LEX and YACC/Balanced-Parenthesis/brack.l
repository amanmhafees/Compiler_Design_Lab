%{
    #include<stdio.h>
    #include "y.tab.h"
    #include<stdlib.h>
%}
%%
"(" {return Open;}
")" {return Close;}
[ \t\n]+ ;
.   ;
%%
int yywrap(){
    return 1;
}