//implement top down parser recursive decsnt parser using c for the given grammar
// E -> TE'
// E'-> +TE' | ε
// T -> FT'
// T'-> *FT' | ε
// F -> (E) | id
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void E();
void E_();
void T();
void T_();
void F();
void error();

char input[100];
int index = 0;
char lookahead;
int step = 1;

void printStep(const char *production) {
    printf("%-5d | %-15s | %s\n", step++, production, input + index);
}

void E() {
    printStep("E -> T E'");
    T();
    E_();
}

void E_() {
    if (lookahead == '+') {
        printStep("E' -> + T E'");
        lookahead = input[++index];
        T();
        E_();
    } else {
        printStep("E' -> ε");
    }
}

void T() {
    printStep("T -> F T'");
    F();
    T_();
}

void T_() {
    if (lookahead == '*') {
        printStep("T' -> * F T'");
        lookahead = input[++index];
        F();
        T_();
    } else {
        printStep("T' -> ε");
    }
}

void F() {
    if (lookahead == 'i' && input[index + 1] == 'd') {
        printStep("F -> id");
        index += 2;  // consume "id"
        lookahead = input[index];
    } else if (lookahead == '(') {
        printStep("F -> (E)");
        lookahead = input[++index];
        E();
        if (lookahead == ')') {
            lookahead = input[++index];
        } else {
            error();
        }
    } else {
        error();
    }
}

void error() {
    printf("\nError in parsing\n");
    exit(1);
}

int main() {
    printf("Enter the input string (end with $): ");
    scanf("%s", input);
    lookahead = input[index];

    printf("\nStep  | Production      | Remaining Input\n");
    printf("--------------------------------------------\n");

    E();

    if (lookahead == '$') {
        printf("--------------------------------------------\n");
        printf("String accepted \n");
    } else {
        error();
    }
    return 0;
}
