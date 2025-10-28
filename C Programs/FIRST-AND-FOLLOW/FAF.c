#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int production_count, ntCount = 0;
char production[20][20];
char nonTerminals[20];
char First[20][20], Follow[20][20];

int isNonTerminal(char c) {
    return isupper(c);
}

void addToSet(char *set, char c) {
    if (!strchr(set, c)) {
        int len = strlen(set);
        set[len] = c;
        set[len + 1] = '\0';
    }
}

int indexOfNT(char c) {
    for (int i = 0; i < ntCount; i++) {
        if (nonTerminals[i] == c)
            return i;
    }
    return -1;
}

void computeFirst(char symbol, char *result) {
    // Terminal or epsilon
    if (!isNonTerminal(symbol)) {
        addToSet(result, symbol);
        return;
    }

    // For each production A -> α
    for (int i = 0; i < production_count; i++) {
        if (production[i][0] == symbol) {
            // RHS starts at index 3 (after A->)
            if (production[i][3] == 'e') {
                addToSet(result, 'e');
            } else {
                int j = 3;
                while (production[i][j] != '\0') {
                    char temp[20] = "";
                    computeFirst(production[i][j], temp);

                    // Add all non-epsilon symbols from FIRST(Xj)
                    for (int k = 0; temp[k] != '\0'; k++)
                        if (temp[k] != 'e')
                            addToSet(result, temp[k]);

                    // Stop if epsilon not found in FIRST(Xj)
                    if (!strchr(temp, 'e'))
                        break;

                    // If reached end, add epsilon to FIRST(A)
                    if (production[i][j + 1] == '\0')
                        addToSet(result, 'e');

                    j++;
                }
            }
        }
    }
}

void computeFollow(char symbol, char *result) {
    if (symbol == nonTerminals[0])
        addToSet(result, '$'); // Start symbol gets $

    for (int i = 0; i < production_count; i++) {
        char head = production[i][0]; // A in A->α

        for (int j = 3; production[i][j] != '\0'; j++) {
            if (production[i][j] == symbol) {
                int k = j + 1;
                int epsilon_chain = 1;

                // Process all symbols after this occurrence of 'symbol'
                while (production[i][k] != '\0' && epsilon_chain) {
                    char temp[20] = "";
                    computeFirst(production[i][k], temp);

                    epsilon_chain = 0;

                    // Add FIRST(next symbol) except epsilon
                    for (int t = 0; temp[t] != '\0'; t++) {
                        if (temp[t] != 'e')
                            addToSet(result, temp[t]);
                    }

                    // If epsilon in FIRST(next symbol), continue further
                    if (strchr(temp, 'e')){
                        epsilon_chain = 1;
                        k++;
                    }

                    //else
                      //  epsilon_chain = 0;


                }

                // If end of RHS or all following can derive ε
                if (production[i][k] == '\0' && symbol != head) {
                    char tempF[20] = "";
                    computeFollow(head, tempF);
                    for (int t = 0; tempF[t] != '\0'; t++)
                        addToSet(result, tempF[t]);
                }
            }
        }
    }
}



void computeFirstFollow() {
    for (int i = 0; i < ntCount; i++) {
        char res[20] = "";
        computeFirst(nonTerminals[i], res);
        strcpy(First[i], res);
    }

    for (int i = 0; i < ntCount; i++) {
        char res[20] = "";
        computeFollow(nonTerminals[i], res);
        strcpy(Follow[i], res);
    }

    printf("\n--- FIRST and FOLLOW Sets ---\n");
    for (int i = 0; i < ntCount; i++) {
        printf("FIRST(%c) = { ", nonTerminals[i]);
        for (int j = 0; First[i][j] != '\0'; j++)
            printf("%c ", First[i][j]);
        printf("}\n");

        printf("FOLLOW(%c) = { ", nonTerminals[i]);
        for (int j = 0; Follow[i][j] != '\0'; j++)
            printf("%c ", Follow[i][j]);
        printf("}\n");
    }
}

int main() {
    printf("Enter number of productions: ");
    scanf("%d", &production_count);
    getchar();

    printf("Enter productions (e.g., E->E+T or T->e without spaces):\n");
    for (int i = 0; i < production_count; i++) {
        scanf("%s", production[i]);
        if (indexOfNT(production[i][0]) == -1)
            nonTerminals[ntCount++] = production[i][0];
    }

    computeFirstFollow();
    return 0;
}
