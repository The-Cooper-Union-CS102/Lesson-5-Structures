#include <stdio.h>
#include <stdlib.h>

typedef struct Number {
    int type;
    union {
        int intVal;
        double doubleVal;
    } vals;
} Number;

Number timesTwo(Number n) {
    Number m;
    m.type = n.type;
    if (n.type == 0) {
        m.vals.intVal = 2*n.vals.intVal;
    } else {
        m.vals.doubleVal = 2*n.vals.doubleVal;
    }
    return m;
}

int main() {
    Number n;
    Number m;
    n.type = 0;
    n.vals.intVal = 7;
    m = timesTwo(n);
    printf("%d\n", m.vals.intVal);
}
