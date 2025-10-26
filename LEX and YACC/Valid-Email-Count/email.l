%{
#include<stdio.h>
#include "y.tab.h"
extern FILE *yyin;
%}
%%
[_a-zA-Z0-9.]+@[a-zA-Z]+\.[a-zA-Z]{2,4} {return EMAIL;}
[ \t\n] ;
. ;
%%

int yywrap(){
    return 1;
}