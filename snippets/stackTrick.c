#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Memory {
    char type; // Either F(ree) or A(llocate)
    long pointer;
} Memory;

typedef struct Node {
    struct Node *next;
    Memory symbol;
} Node;

typedef struct Stack {
    Node *sentinel;
    Node *top;
} Stack;

Memory MEMORY[100];
Memory *MEMORY_PTR = MEMORY;

void track(char type, void *ptr) {
    MEMORY_PTR->pointer = (long) ptr;
    MEMORY_PTR->type = type;
    MEMORY_PTR++;
}

Stack *makeStack() {
    Stack *sp = (Stack *) malloc(sizeof(Stack));
    track('A', sp);
    Node *np = (Node *) malloc(sizeof(Node));
    track('A', np);
    np->next = NULL;
    np->symbol.type = 'N';
    np->symbol.pointer = 0;
    sp->sentinel = np;
    sp->top = np;
    return sp;
}

void push(Stack *sp, Memory m) {
    // Initialize new Node
    Node *np = (Node *) malloc(sizeof(Node));
    track('A', np);
    np->next = sp->top;
    np->symbol = m;
    // Add it to the Stack
    sp->top = np;
}

Memory pop(Stack *sp) {
    Memory m = sp->top->symbol;
    free(sp->top);
    track('F', sp->top);
    sp->top = sp->top->next;
    return m;
}

int empty(Stack *sp) {
    return (sp->top->next == NULL);
}

void freeStack(Stack *sp) {
    Node *np = sp->top;
    Node *tnp = np;
    while (np) {
        tnp = np->next;
        free(np);
        track('F', np);
        np = tnp;
    }
    free(sp);
    track('F', sp);
}

int balanced(Memory M[]) {
    Memory *mPtr = M;
    Stack *sp = makeStack();
    Memory m;
    for (; (mPtr->type != 'N'); mPtr++) {
        m = *mPtr;
        printf("(%c, %ld)\n", m.type, m.pointer);
        if (m.type == 'A') {
            push(sp, m);
        }
        if (m.type == 'F' && sp->top->symbol.type == 'A' &&
                m.pointer == sp->top->symbol.pointer) {
            pop(sp);
        } else if (m.type == 'F') {
            push(sp, m);
        }
    }
    int retval;
    if (empty(sp)) {
        retval = 1;
    } else {
        retval = 0;
    }
    freeStack(sp);
    return retval;
}

int main() {
    Memory M1[10] = {
        {'A', 1},
        {'F', 1},
        {'A', 2},
        {'F', 2},
        {'F', 3},
        {'N', 0},
    };
    printf("%d\n", balanced(M1));
    Memory M2[10] = {
        {'A', 1},
        {'F', 1},
        {'A', 2},
        {'F', 2},
        {'N', 0},
    };
    printf("%d\n", balanced(M2));
}
