#include <stdio.h>

struct Point {
    int x;
    int y;
};

struct Point makePoint(int x, int y) {
    struct Point p;
    p.x = x;
    p.y = y;
    return p;
}

struct Point addPoints(struct Point p1, struct Point p2) {
    struct Point p;
    p.x = p1.x + p2.x;
    p.y = p1.y + p2.y;
    return p;
}

int main() {
    struct Point p1 = makePoint(3, 4);
    struct Point p2 = makePoint(4, 5);
    struct Point pt = addPoints(p1, p2);
    printf("(%d, %d)\n", pt.x, pt.y);
}
