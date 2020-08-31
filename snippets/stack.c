#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


typedef struct Node {
    struct Node *next;
    char symbol;
} Node;

typedef struct Stack {
    Node *sentinel;
    Node *top;
} Stack;

Stack *makeStack() {
    Stack *sp = (Stack *) malloc(sizeof(Stack));
    Node *np = (Node *) malloc(sizeof(Node));
    np->next = NULL;
    np->symbol = '!';
    sp->sentinel = np;
    sp->top = np;
    return sp;
}

void push(Stack *sp, char c) {
    // Initialize new Node
    Node *np = (Node *) malloc(sizeof(Node));
    np->next = sp->top;
    np->symbol = c;
    // Add it to the Stack
    sp->top = np;
}

char pop(Stack *sp) {
    char c = sp->top->symbol;
    free(sp->top);
    sp->top = sp->top->next;
    return c;
}

int empty(const Stack *sp) {
    return (sp->top->next == NULL);
}

void printNode(Node *n) {
    printf("(%p, '%c')\n", n->next, n->symbol);
}

void printStack(const Stack *sp) {
    printf("---Stack Start---\n");
    Node *np = sp->top;
    while (np->next) {
        printNode(np);
        np = np->next;
    }
    printf("---Stack End---\n");
}

void freeStack(Stack *sp) {
    Node *np = sp->top;
    Node *tnp = np;
    while (np) {
        tnp = np->next;
        free(np);
        np = tnp;
    }
    free(sp);
}

int balanced(const char *str) {
    Stack *sp = makeStack();
    char c;
    for (; (c = *str); str++) {
        if (c == '(' || c == '[') {
            push(sp, c);
        }
        if (c == ')') {
            if (sp->top->symbol == '(') {
                pop(sp);
            } else {
                push(sp, c);
            }
        }
        if (c == ']') {
            if (sp->top->symbol == '[') {
                pop(sp);
            } else {
                push(sp, c);
            }
        }
    }
    int retval = empty(sp);
    freeStack(sp);
    return retval;
}

int main() {
    assert(balanced("()())") == 0);
    assert(balanced("(a)b") == 1);
    assert(balanced("(ab") == 0);
    assert(balanced("[(])") == 0);
    assert(balanced("[]()") == 1);
    assert(balanced("[a(cd)b]-(f{h}g)") == 1);
    assert(balanced("[a(cd)b]-[(f{h}g)") == 0);
}
