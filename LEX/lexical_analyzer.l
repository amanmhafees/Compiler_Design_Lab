

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

/* Sample input.txt content: */
/* int a = 10; */
/* float b = 3.5; */
/* char c = 'x'; */

/* if (a < b) { */
/*     a = a + 1; */
/* } else { */
/*     b = b - 2; */
/* } */

/* for (int i = 0; i < 5; i++) { */
/*     a = a * 2; */
/* } */

/* while (a > 0) { */
/*     a = a - 1; */
/* } */
