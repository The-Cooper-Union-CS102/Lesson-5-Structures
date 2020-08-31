#include <stdio.h>
#include <stdlib.h>

typedef union Number {
    int intVal;
    double doubleVal;
} Number;

Number timesTwo(Number n, int type) {
    Number m;
    if (type == 0) {
        m.intVal = 2*n.intVal;
    } else {
        m.doubleVal = 2*n.doubleVal;
    }
    return m;
}

int main() {
    Number n;
    Number m;
    n.intVal = 7;
    m = timesTwo(n, 0);
    printf("%d\n", m.intVal);
}
