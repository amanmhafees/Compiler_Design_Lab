#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

int is_keyword(const char *s){
    const char *keywords[] = {
    "int", "char", "float", "if", "else", "for", "while",
    "do", "return", "void", "printf", "scanf", "main"
    };
    int i;
    int kw_num=13;
    for(i=0;i<kw_num;i++){
        if(strcmp(s,keywords[i])==0){
            return 1;
        }
    }
    return 0;
}

int main(){
    FILE *input;
    char str[100],ch;
    int i;
    input=fopen("input.txt","r");
    if (!input) {
        printf("File not found!\n");
        return 1;
    }
    printf("\n--------------------------------------------\n");
    printf("| %-15s | %-20s |\n", "Lexeme", "Token Type");
    printf("--------------------------------------------\n");

    while((ch=fgetc(input))!=EOF){
        if(isspace(ch)){
            continue;
        }
        if(isalpha(ch) || ch=='_'){
            i=0;
            str[i++]=ch;
            while((ch=fgetc(input))!=EOF && (isalnum(ch) || ch=='_')){
                str[i++]=ch;
            }
            str[i]='\0';
            if(is_keyword(str)){
                printf("| %-15s | %-20s |\n",str, "Keyword");
            }
            else{
                printf("| %-15s | %-20s |\n",str, "Identifier");
            }
            ungetc(ch,input);
        }
        else if(isdigit(ch)){
            i=0;
            str[i++]=ch;
            int hasDot=0;
            while((ch=fgetc(input))!=EOF&&(isdigit(ch) || ch=='.')){
                if(ch=='.'){
                    hasDot=1;
                }
                str[i++]=ch;
            }
            str[i]='\0';
            if(hasDot){
                printf("| %-15s | %-20s |\n",str, "FLOAT");
            }else{
                printf("| %-15s | %-20s |\n",str, "INTEGER");
            }
            ungetc(ch,input);
        }
        //strings
        else if(ch=='"'){
            i=0;
            str[i++]=ch;
            while ((ch = fgetc(input)) != EOF && ch != '"')
                str[i++] = ch;
            str[i++] = '"';
            str[i] = '\0';
            printf("| %-15s | %-20s |\n", str, "String Literal");
        }
        //comment or division
        else if(ch=='/'){
            char next=fgetc(input);
            if(next=='/'){
                while ((ch = fgetc(input)) != EOF && ch != '\n');
            }
            else if(next=='*'){
                char prev;
                while ((ch = fgetc(input)) != EOF) {
                    if (prev == '*' && ch == '/') break;
                    prev = ch;
                }
            }else {
                printf("| %-15c | %-20s |\n", ch, "Operator");
                ungetc(next, input);
            }
        }

        //operator
        else if(strchr("+-=<>!",ch)){
            char next = fgetc(input);
            if (next == '=' || (ch == '+' && next == '+') || (ch == '-' && next == '-'))
                printf("| %c%c           | %-20s |\n", ch, next, "Operator");
            else {
                printf("| %-15c | %-20s |\n", ch, "Operator");
                ungetc(next, input);
            }
        }
        else if (strchr(";,(){}", ch))
            printf("| %-15c | %-20s |\n", ch, "Special Symbol");
    }
    fclose(input);
    return 0;

}