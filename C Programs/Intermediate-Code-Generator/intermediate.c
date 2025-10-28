#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

int top=-1;
char stack[20];
void push(char s){
    stack[++top]=s;
}

char pop(){
    return stack[top--];
}
int precedence(char c) {
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    return 0;
}
void infixToPostfix(char infix[],char postfix[]){
    int i,j=0;
    char ch;
    top=-1;

    for(i=0;infix[i]!='\0';i++){
        ch=infix[i];
        if(isalnum(ch)){
            postfix[j++]=ch;
        }
        else if(ch=='('){
            push(ch);
        }
        else if(ch==')'){
            while(top!=-1 && stack[top]!='('){
                postfix[j++]=pop();
            }
        }
        else if(ch=='+'||ch=='-'||ch=='*'||ch=='/'){
            while (top != -1 && precedence(stack[top]) >= precedence(ch))
                postfix[j++] = pop();
            push(ch);
        }
    }
    while (top != -1)                      // Pop remaining operators
        postfix[j++] = pop();

    postfix[j] = '\0';
}

void generateTAC(char postfix[], char lhs) {
    char tempStack[50][10];
    int tTop = -1, tempCount = 1;
    char result[10];

    for(int i=0;i<strlen(postfix);i++){
        char symbol=postfix[i];

        if(isalnum(symbol)){
            char op[2]={symbol,'\0'};
            strcpy(tempStack[++tTop],op);
        }
        else if(symbol=='+'|| symbol=='-' || symbol=='*' || symbol=='/'){
            char op2[10],op1[10];
            strcpy(op2,tempStack[tTop--]);
            strcpy(op1,tempStack[tTop--]);

            sprintf(result, "t%d", tempCount++);
            printf("%s = %s %c %s\n", result, op1, symbol, op2);

            // Push result back
            strcpy(tempStack[++tTop], result);
        }
    }
    printf("%c = %s\n", lhs, tempStack[tTop]);
}

int main(){
    char expr[50], lhs, rhs[50], postfix[50];

    printf("Enter expression (e.g. a=b+c*d): ");
    scanf("%s", expr);

    if(strchr(expr,'=')==NULL){
        printf("Error: Expression must contain '='.\n");
        exit(0);
    }
    lhs=expr[0];
    strcpy(rhs,expr+2);

    infixToPostfix(rhs,postfix);
    printf("\nPostfix: %s\n",postfix);

    printf("\n--- Three Address Code ---\n");
    generateTAC(postfix, lhs);

    return 0;

}