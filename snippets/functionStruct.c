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

int main() {
    struct Point pt = makePoint(3, 4);
    printf("(%d, %d)\n", pt.x, pt.y);
}
