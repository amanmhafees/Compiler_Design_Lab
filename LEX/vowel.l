/*flex vowel.l*/
/* gcc lex.yy.c*/
/* ./a.out*/
/*Enter a string and press Ctrl+D when done:*/
/*aman*/
/*Vowels: 2*/
/*Consonants: 2*/

%{
    #include<stdio.h>
    int vowels=0;
    int consonants=0;
%}
%%
[aeiouAEIOU] {vowels++;}
[b-df-hj-np-tv-zB-DF-HJ-NP-TV-Z] {consonants++;}
.|\n          ; /* Ignore all other characters */
%%
int main(){
    printf("Enter a string and press Ctrl+D when done:\n");
    yylex();
    printf("Vowels: %d\n",vowels);

    printf("Consonants: %d\n",consonants);
    return 0;
}
int yywrap(){
    return 1;
}