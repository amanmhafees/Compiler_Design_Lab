%{
    #include<stdio.h>
    int yylex();
    void yyerror(char *s);
    int count=0;
%}

%token Open Close

%%
input:

    |input expr
    ;
expr:
    Open {count++;}
    |Close {count--;}
%%
void main(){
    printf("Enter the string: ");
    yyparse();
    if(count==0){
        printf("Balanced\n");
    }else{
        printf("Unbalanced\n");
    }
}

void yyerror(char *s){
    printf("Error ocuured: %s",s);
}