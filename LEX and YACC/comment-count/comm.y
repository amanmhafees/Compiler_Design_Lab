%{
    #include<stdio.h>
    #include<stdlib.h>

    extern FILE *yyin;
    int yylex();
    void yyerror(char *s);
    int Single_count=0;
    int Multi_count=0;
%}

%token Single_line Multi_line

%%
input:
    
    |input expr
    ;
expr:
    Single_line {Single_count++;}
    |Multi_line {Multi_count++;}
    ;
%%
void main(){
    yyin=fopen("input.txt","r");
    if (!yyin) {
        printf("Cannot open input.txt\n");
        exit(1);
    }
    yyparse();
    printf("Single line: %d\n",Single_count);
    printf("Multi line: %d\n",Multi_count);
    printf("Total: %d\n",Single_count+Multi_count);
    fclose(yyin);
}
void yyerror(char *s){
    printf("Error occured %s\n",s);
}
