#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define MAXLEN 256
#define MAXWORDS 100000

char *lines[MAXWORDS];

typedef struct BstNode {
    char *string;
    struct BstNode *less;
    struct BstNode *more;
} BstNode;

BstNode *makeBstNode(char *string) {
    BstNode *np = (BstNode *) malloc(sizeof(BstNode));
    np->less = NULL;
    np->more = NULL;
    np->string = string;
    return np;
}

void insert(BstNode *np, char *string) {
    int cmp = strcmp(string, np->string);
    if (cmp < 0) { // string < np->string
        if (np->less == NULL) {
            BstNode *new = makeBstNode(string);
            np->less = new;
        } else {
            insert(np->less, string);
        }
    } else if (cmp > 0) { // string > np->string
        if (np->more == NULL) {
            BstNode *new = makeBstNode(string);
            np->more = new;
        } else {
            insert(np->more, string);
        }
    }
}

int contains(BstNode *np, char *string) {
    int cmp = strcmp(string, np->string);
    if (cmp == 0) {
        return 1;
    }
    BstNode *nextNode = (cmp < 0) ? np->less : np->more;
    if (nextNode == NULL) {
        return 0;
    } else {
        return contains(nextNode, string);
    }
}

int naiveDupCheck(char *a[], int len) {
    int m, n;
    for (m = 0; m < len; m++) {
        for (n = m+1; n < len; n++) {
            if (strcmp(a[m], a[n]) == 0) {
                return 1;
            }
        }
    }
    return 0;
}

int dupCheck(char *a[], int len) {
    BstNode *bstp = makeBstNode(a[0]);
    int n;
    for (n = 1; n < len; n++) {
        if (contains(bstp, a[n])) {
            return 1;
        }
        insert(bstp, a[n]);
    }
    return 0;
}

int loadLines(char *filename) {
    int lineno = 0;
    char line[MAXLEN];
    FILE *fp = fopen(filename, "r");
    printf("Starting loading in words...\n");
    while (fgets(line, MAXLEN, fp) > 0) {
        int len = strlen(line);
        assert(line[len-1] == '\n' && "Input too long!");
        line[len-1] = '\0'; // Strip newline
        char *newline = (char *) malloc(sizeof(char) * len);
        strcpy(newline, line);
        lines[lineno] = newline;
        lineno += 1;
    }
    return lineno;
}

int main(int argc, char *argv[]) {
    int argnum = 1;
    int useFast = 0;
    char *filename;
    while (argnum < argc) {
        if (strcmp(argv[argnum], "--fast") == 0) {
            useFast = 1;
        }
        if (strcmp(argv[argnum], "-i") == 0) {
            argnum += 1;
            filename = argv[argnum];
        }
        argnum += 1;
    }
    assert(filename && "Filename must be provided with -i");
    int lineno = loadLines(filename);
    printf("Done loading in words...\n");
    if (useFast) {
        printf("Starting fast duplicate check...\n");
        printf("Duplicate? %d\n", dupCheck(lines, lineno));
    } else {
        printf("Starting naive duplicate check...\n");
        printf("Duplicate? %d\n", naiveDupCheck(lines, lineno));
    }
}
