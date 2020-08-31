#include <stdio.h>

struct Student {
    char *name;
    int grade;
};

int main() {
    struct Student students[] = {
        {"Ross", 90},
        {"Cory", 65},
        {"Gordon", 80},
        {"Deborah", 100},
    };
    printf("%s's grade: %d\n", students[0].name, students[0].grade);
}
