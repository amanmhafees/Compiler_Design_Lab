%{
#include<stdio.h>
#include "y.tab.h"
extern FILE *yyin;
%}
%%
"//" {return Single_line;}
"/*" {return Multi_line;}
[ \t\n] ;
. ;
%%
int yywrap(){
    return 1;
}
