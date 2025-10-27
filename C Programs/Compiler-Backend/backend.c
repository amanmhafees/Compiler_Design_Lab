#include<stdio.h>
#include<string.h>

void main(){

    char icode[10][30],str[20],opr[10];
    int i=0;
    printf("Enter the set of intermediate code{Enter EXIT to exit}");
    do{
        scanf("%s",icode[i]);
    }while(strcmp(icode[i++],"EXIT")!=0);
    printf("Corresponding target code generation\n");
    i=0;
    do{
        strcpy(str,icode[i]);
        switch(str[3]){
            case '+':
                strcpy(opr,"ADD");
                break;
            case '-':
                strcpy(opr,"SUB");
                break;
            case '*':
                strcpy(opr,"MUL");
                break;
            case '/':
                strcpy(opr,"DIV");
                break;
        }
        printf("\n\tMOV %c,R%d",str[2],i);
        printf("\n\t%s R%d,%c",opr,i,str[4]);
        printf("\n\tMov R%d,%c",i,str[0]);
    }while(strcmp(icode[++i],"EXIT")!=0);
    printf("\n");
}