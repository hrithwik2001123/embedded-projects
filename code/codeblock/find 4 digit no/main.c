#include <stdio.h>

int main() {
    int a, b, c, d;

    // Prompting user to input four numbers
    printf("Enter four numbers:\n");
    scanf("%d %d %d %d", &a, &b, &c, &d);

    if (a >= b) {
        if (a >= c) {
            if (a >= d) {
                printf("a is the greatest: %d\n", a);
            } else {
                printf("d is the greatest: %d\n", d);
            }
        } else {
            if (c >= d) {
                printf("c is the greatest: %d\n", c);
            } else {
                printf("d is the greatest: %d\n", d);
            }
        }
    } else {
        if (b >= c) {
            if (b >= d) {
                printf("b is the greatest: %d\n", b);
            } else {
                printf("d is the greatest: %d\n", d);
            }
        } else {
            if (c >= d) {
                printf("c is the greatest: %d\n", c);
            } else {
                printf("d is the greatest: %d\n", d);
            }
        }
    }

    return 0;
}
