%{
#include <stdio.h>
#include <stdlib.h>

extern FILE *yyin;
FILE *fout;   // file to write modified code

int p = 0;    // printf count
int s = 0;    // scanf count
%}

%%

"printf" {
    p++;
    printf("readf");       // print replacement to screen
    fprintf(fout, "readf"); // write replacement to file
}

"scanf" {
    s++;
    printf("writef");       
    fprintf(fout, "writef");
}

.|\n { 
    // copy all other characters as-is
    printf("%s", yytext);
    fprintf(fout, "%s", yytext);
}

%%

int main() {
    yyin = fopen("input.txt", "r");
    if (!yyin) {
        printf("Could not open input.txt\n");
        return 1;
    }

    fout = fopen("output.txt", "w");
    if (!fout) {
        printf("Could not open output.txt\n");
        return 1;
    }

    yylex(); // run lexer

    fclose(yyin);
    fclose(fout);

    printf("\n\nNumber of printf: %d\n", p);
    printf("Number of scanf: %d\n", s);

    return 0;
}

int yywrap() {
    return 1;
}
