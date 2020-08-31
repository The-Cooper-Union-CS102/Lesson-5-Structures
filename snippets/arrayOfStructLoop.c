#include <stdio.h>

struct Student {
    char *name;
    int grade;
};

int main() {
    struct Student students[] = {
        {"Ross", 90},
        {"Cory", 80},
        {"Gordon", 80},
        {"Deborah", 100},
    };
    int n;
    int numStudents = sizeof(students) / sizeof(struct Student);
    for (n = 0; n < numStudents; n++) {
        printf("%s's grade: %d\n", students[n].name, students[n].grade);
    }
}
