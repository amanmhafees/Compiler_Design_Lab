%{
    #include<stdio.h>
    extern FILE *yyin;
%}
%%
"int"|"float"|"char"|"double"|"if"|"else"|"for"|"while" {printf("Keyword: %s\n",yytext);}
[a-zA-Z_][a-zA-Z0-9_]* {printf("Identifier: %s\n",yytext);}
[0-9]+(\.[0-9]+)* {printf("Number: %s\n",yytext);}
[+\-*/=<>] {printf("Operator: %s\n",yytext);}
[ \t\n] ; /* Ignore whitespace */
[;] {printf("Separator: %s\n",yytext);}
[{}] {printf("Curly braces: %s\n",yytext);}
%%
int main(){
    yyin=fopen("input.txt","r");
    if(!yyin){
        printf("Could not open file\n");
        return 1;
    }
    yylex();
    fclose(yyin);
    return 0;
}
int yywrap(){
    return 1;
}