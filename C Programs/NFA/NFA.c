#include <stdio.h>
#include <stdlib.h>

#define MAX_STATES 20
#define MAX_TRANSITIONS 50

struct transition {
    int from;
    char input;
    int to;
};

struct transition transitions[MAX_TRANSITIONS];
int num_transitions = 0;
int closure[MAX_STATES];
int closure_count = 0;

int in_closure(int state) {
    for (int i = 0; i < closure_count; i++) {
        if (closure[i] == state)
            return 1;
    }
    return 0;
}

void find_epsilon_closure(int state) {
    if (!in_closure(state))
        closure[closure_count++] = state;

    for (int i = 0; i < num_transitions; i++) {
        if (transitions[i].from == state &&
            transitions[i].input == 'e' &&
            !in_closure(transitions[i].to)) {
            find_epsilon_closure(transitions[i].to);
        }
    }
}

int main() {
    printf("Enter the number of transitions: ");
    scanf("%d", &num_transitions);

    printf("\nEnter the transitions in the format (e.g., q0 0 q1 or q0 e q2):\n");
    for (int i = 0; i < num_transitions; i++) {
        printf("Transition %d:\n", i + 1);
        printf("From state: ");
        scanf("%d", &transitions[i].from);
        printf("Input: ");
        scanf(" %c", &transitions[i].input);
        printf("To state: ");
        scanf("%d", &transitions[i].to);
    }

    // Print all transitions
    printf("\n--- Transitions ---\n");
    for (int i = 0; i < num_transitions; i++) {
        printf("q%d --%c--> q%d\n", transitions[i].from, transitions[i].input, transitions[i].to);
    }

    // Find all unique states
    int max_state = 0;
    for (int i = 0; i < num_transitions; i++) {
        if (transitions[i].from > max_state) max_state = transitions[i].from;
        if (transitions[i].to > max_state) max_state = transitions[i].to;
    }

    printf("\n--- Epsilon Closures ---\n");
    for (int s = 0; s <= max_state; s++) {
        closure_count = 0;
        find_epsilon_closure(s);
        printf("ε-closure(q%d): { ", s);
        for (int i = 0; i < closure_count; i++) {
            printf("q%d ", closure[i]);
        }
        printf("}\n");
    }

    return 0;
}
