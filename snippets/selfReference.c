#include <stdio.h>

struct Node {
    int value;
    struct Node *next;
};

int main() {
    struct Node n1 = {0, NULL};
    struct Node n2 = {0, &n1};
}
