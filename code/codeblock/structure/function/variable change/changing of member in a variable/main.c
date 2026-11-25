#include <stdio.h>
#include <string.h>  // for strcpy

struct std {
    char name[10];
    int rollno;
};

void function(struct std *s2) {
    strcpy(s2->name, "hello");
    s2->rollno = 2;
}

int main() {
    struct std s1 = {"hrithwik", 10};
    struct std s2;

    function(&s2);
    printf("%s\n%d", s2.name, s2.rollno);

    return 0;
}
