#include <stdio.h>
#include <stdlib.h>

struct Node {
    struct Node *next;
    char *str;
};

int main(int argc, char *argv[]) {
    struct Node n = {NULL, ""};
    struct Node *sp = &n; // Starting pointer
    struct Node *cp = &n; // Current pointer
    int i;
    for (i = 1; i < argc; i++) {
        // Initialize new Node
        struct Node *new = (struct Node *) malloc(sizeof(struct Node));
        new->str = argv[i];
        new->next = NULL;
        // Set current pointer to next node
        cp->next = new;
        cp = cp->next;
    }
    // Print Nodes in order
    cp = sp;
    while (cp->next) {
        printf("(%p, %s)->", cp->next->next, cp->next->str);
        cp = cp->next;
    }
    printf("\n");
}
