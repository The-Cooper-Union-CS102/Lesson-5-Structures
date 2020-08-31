#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define MAXLEN 256
#define MAXLINES 100000

char *USERNAMES[MAXLINES];

typedef struct BstNode {
    char *key;
    int *value;
    struct BstNode *less;
    struct BstNode *more;
} BstNode;

BstNode *makeBstNode(char *key, int value) {
    BstNode *np = (BstNode *) malloc(sizeof(BstNode));
    np->less = NULL;
    np->more = NULL;
    np->key = key;
    np->value = (int *) malloc(sizeof(int));
    *(np->value) = value;
    return np;
}

void insert(BstNode *np, char *key, int value) {
    int cmp = strcmp(key, np->key);
    if (cmp < 0) { // key < np->key
        if (np->less == NULL) {
            BstNode *new = makeBstNode(key, value);
            np->less = new;
        } else {
            insert(np->less, key, value);
        }
    } else if (cmp > 0) { // key > np->key
        if (np->more == NULL) {
            BstNode *new = makeBstNode(key, value);
            np->more = new;
        } else {
            insert(np->more, key, value);
        }
    }
}

void print(BstNode *np) {
    if (np) {
        print(np->less);
        printf("%s: %d\n", np->key, *np->value);
        print(np->more);
    }
}

int *get(BstNode *np, char *key) {
    int cmp = strcmp(key, np->key);
    if (cmp == 0) {
        return np->value;
    }
    BstNode *nextNode = (cmp < 0) ? np->less : np->more;
    if (nextNode == NULL) {
        return NULL;
    } else {
        return get(nextNode, key);
    }
}

int loadUsernames(char *filename) {
    int lineno = 0;
    char line[MAXLEN];
    char* username;
    FILE *fp = fopen(filename, "r");
    while (fgets(line, MAXLEN, fp) > 0) {
        int len = strlen(line);
        assert(line[len-1] == '\n' && "Input too long!");
        line[len-1] = '\0'; // Strip newline
        username = (char *) malloc(sizeof(char) * len);
        strcpy(username, line);
        USERNAMES[lineno] = username;
        lineno += 1;
    }
    return lineno;
}

void printCount(char *strings[], int len) {
    int count = 0;
    BstNode *root = makeBstNode(strings[0], 1);
    for (int n = 1; n < len; n++) {
        char *string = strings[n];
        int *got;
        if ((got = get(root, string))) {
            (*got) += 1;
        } else {
            insert(root, string, 1);
        }
    }
    print(root);
}

int main(int argc, char *argv[]) {
    int argnum = 1;
    int useFast = 0;
    char *databaseFilename;
    char *usersFilename;
    while (argnum < argc) {
        if (strcmp(argv[argnum], "--fast") == 0) {
            useFast = 1;
        }
        if (strcmp(argv[argnum], "-u") == 0) {
            argnum += 1;
            usersFilename = argv[argnum];
        }
        argnum += 1;
    }
    assert(usersFilename && "users must be provided with -u");
    int lineno = loadUsernames(usersFilename);
    printf("Loaded %d lines.\n", lineno);
    printCount(USERNAMES, lineno);
    printf("Done loading in words...\n");
}
