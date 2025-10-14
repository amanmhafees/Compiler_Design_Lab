%{
    #include <stdio.h>
    #include <stdlib.h>
    void yyerror(char *s);
    int yylex(void);
    extern char *yytext;   // <-- Add this so yytext is visible
%}

%token ID

%%
start:
    ID { printf("Valid identifier: %s\n", yytext); }
    ;
%%

int main() {
    printf("Enter a variable name: ");
    yyparse();
    return 0;
}

void yyerror(char *msg) {
    printf("Invalid identifier\n");
}
