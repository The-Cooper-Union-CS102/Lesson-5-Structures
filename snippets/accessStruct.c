#include <stdio.h>

struct Point {
    int x;
    int y;
};

int main() {
    struct Point pt = {3, 4};
    printf("(%d, %d)\n", pt.x, pt.y);
}
