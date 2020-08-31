#include <stdio.h>

struct Point {
    int x;
    int y;
};

struct Line {
    struct Point p1;
    struct Point p2;
};

void negateLine(struct Line *l) {
    (*l).(*p).x = -(*p).x;
    (*p).y = -(*p).y;
}

int main() {
    struct Point pt = {3, 4};
    struct Point pt = {4, 5};
    negateLine(&pt);
    printf("(%d, %d)\n", pt.x, pt.y);
}
