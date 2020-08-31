#include <stdio.h>

struct Point {
    int x;
    int y;
};

void negatePoint(struct Point *p) {
    (*p).x = -(*p).x;
    (*p).y = -(*p).y;
}

int main() {
    struct Point pt = {3, 4};
    negatePoint(&pt);
    printf("(%d, %d)\n", pt.x, pt.y);
}
