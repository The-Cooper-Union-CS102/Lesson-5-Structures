#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct Node {
    struct Node *next;
    int digit;
} Node;

Node *makeNode(Node *np, int digit) {
    Node *newPtr = (Node *) malloc(sizeof(Node));
    newPtr->next = np;
    newPtr->digit = digit;
    return newPtr;
}

int len(Node *np) {
    int n = 0;
    while (np) {
        n += 1;
        np = np->next;
    }
    return n;
}

Node *add(Node *a, Node *b) {
    int carry = (a->digit + b->digit) > 9;
    int value = (a->digit + b->digit) % 10;
    Node *rs = makeNode(NULL, value);
    Node *r = rs;
    Node z = {NULL, 0};
    Node *zp = &z;
    while (a->next || b->next || carry) {
        a = (a->next) ? a->next : zp;
        b = (b->next) ? b->next : zp;
        r->next = makeNode(NULL, (a->digit + b->digit + carry) % 10);
        carry = (a->digit + b->digit + carry) > 9;
        r = r->next;
    }
    return rs;
}

void printList(Node *np) {
    int index = len(np);
    char c[index+1];
    for (int n = 0; n < index+1; n++) {
        c[n] = '\0';
    }
    while (np) {
        c[--index] = np->digit + '0';
        np = np->next;
    }
    printf("%s\n", c);
}

Node *fromString(char *string) {
    int len = strlen(string);
    Node *sp = makeNode(NULL, string[len-1] - '0');
    Node *np = sp;
    for (int i = len - 2; i >= 0; i--) {
        np->next = makeNode(NULL, string[i] - '0');
        np = np->next;
    }
    return sp;
}

int main(int argc, char *argv[]) {
    assert(argc == 3);
    Node *ap = fromString(argv[1]);
    Node *bp = fromString(argv[2]);
    printList(ap);
    printList(bp);
    Node *sum = add(ap, bp);
    printList(sum);
}
