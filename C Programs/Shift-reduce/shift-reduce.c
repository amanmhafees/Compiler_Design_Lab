// E → E + E  
// E → E * E  
// E → E / E  
// E → a  
// E → b

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char input[20],stack[20];
int top=0,ip=0;
void printStep(const char *action) {
    printf("\n%-10s\t%-10s\t%s", stack, input + ip, action);
}

void reduce(){
    if(stack[top]== 'a' || stack[top]=='b'){
        stack[top]='E';
        stack[top+1]='\0';
        printStep("Reduce E-> id");
    }

    if(stack[top]=='E' &&(stack[top-1]=='+' || stack[top-1]=='/' || stack[top-1]=='*')&&stack[top-2]=='E'){
        char op=stack[top-1];
        top-=2;
        stack[top]='E';
        stack[top+1]='\0';
        char action[20];
        sprintf(action,"Reduce E->E%cE",op);
        printStep(action);
    }
}

int main(){
    printf("SHIFT REDUCE PARSER\n");
    printf("Grammar:\nE->E+E\nE→E*E\nE→E/E\nE→a|b\n");
    printf("\nEnter input string: ");
    scanf("%s", input);
    printf("\nStack\t\tInput\t\tAction");
    printf("\n------------------------------------------");
    strcat(input, "$");
    stack[0]='$';
    stack[1]='\0';
    printStep("--");
    while(1){
        stack[++top]=input[ip++];
        stack[top+1]='\0';
        char action[20];
        sprintf(action,"Shift %c",stack[top]);
        printStep(action);

        reduce();

        if(strcmp(stack,"$E")==0 && input[ip]=='$'){
            printStep("ACCEPT");
            break;
        }
        if (input[ip] == '$' && strcmp(stack, "$E") != 0) {
            printStep("REJECT");
            break;
        }
    }
     printf("\n------------------------------------------\n");
    return 0;
}