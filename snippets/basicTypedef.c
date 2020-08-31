#include <stdio.h>
#include <stdlib.h>

typedef char *String;

struct Node {
    struct Node *next;
    String str;
};

int main() {
    struct Node *np = (struct Node *) malloc(sizeof(struct Node));
    np->str = "Hello";
    np->next = NULL;
    printf("(%p, %s)\n", np->next, np->str);
}
