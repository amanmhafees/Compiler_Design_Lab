%{
    #include<stdio.h>
    #include<stdlib.h>
    #include<string.h>

    FILE *valid_out, *invalid_out;
    extern FILE *yyin;
    int yylex();
    void yyerror(char *s);
%}

%union {
    char *str;
}

%token <str> VALID_EMAIL
%token <str> INVALID_EMAIL

%%
    input:

            |input email
        ;
    email:
        VALID_EMAIL {fprintf(valid_out,"%s\n", $1); free($1);}
        |INVALID_EMAIL {fprintf(invalid_out,"%s\n",$1); free($1);}
        ;
%%
void yyerror(char *msg){
    fprintf(stderr,"Error: %s\n",msg);
}
int main(){
    yyin=fopen("input.txt","r");
    valid_out=fopen("valid_emails.txt","w");
    invalid_out=fopen("invalid_emails.txt","w");
    if (!valid_out || !invalid_out) {
        perror("Cannot open output files");
        exit(1);
    }
    printf("Processing emails....\n");
    yyparse();

    printf("Output saved\n");

    fclose(yyin);
    fclose(invalid_out);
    fclose(valid_out);

    return 0;
}