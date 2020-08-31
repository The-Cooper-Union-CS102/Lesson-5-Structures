#include <stdio.h>

struct Point {
    int x;
    int y;
};

struct Line {
    struct Point p1;
    struct Point p2;
};

int main() {
    struct Point p1 = {3, 4};
    struct Point p2 = {4, 5};
    struct Line line = {p1, p2};
    printf("(%d, %d) -> (%d, %d)\n",
           line.p1.x, line.p1.y, line.p2.x, line.p2.y);
}
