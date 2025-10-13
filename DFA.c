// DFA (Deterministic Finite Automaton) implementation in C
// to design a DFA that accepts language ending with "01".

#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int dfa_checking(char str[]){
    int state=0;
    for(int i=0;i<strlen(str);i++){
        switch(state){
            case 0:
                if(str[i]=='0'){
                    state=1;
                }
                else if (str[i]=='1') {
                    state=0;
                }else{
                    printf("Invalid input\n");
                    exit(0);
                }
                break;
            case 1:
                if(str[i]=='0'){
                    state=1;
                }
                else if (str[i]=='1') {
                   state=2;
                }else{
                    printf("Invalid input\n");
                    exit(0);
                }
                break;
        case 2:
                if(str[i]=='0'){
                    state=1;
                }
                else if(str[i]=='1'){
                    state=0;
                }else{
                    printf("Invalid input\n");
                    exit(0);
                }
        }
    }
    return state;
}

void main(){
    char str[100];
    printf("Enter the string: ");
    scanf("%s",str);
    int final_state=dfa_checking(str);
    if(final_state==2){
        printf("String accepted\n");
    }else{
        printf("String not accepted\n");
    }
}
