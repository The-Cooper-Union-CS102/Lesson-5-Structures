#include <stdio.h>
#include <stdlib.h>

struct Node {
    struct Node *next;
    char *str;
};

int main() {
    struct Node *np = (struct Node *) malloc(sizeof(struct Node));
    np->str = "Hello";
    np->next = NULL;
    printf("(%p, %s)\n", np->next, np->str);
}
