#include <stdio.h>

int main() {
    int a = 0, b = 1, next=1,num;
printf("enter a number ");
scanf("%d",&num);
    while (next <= num) {
        printf(" %d,", next);
        a = b;
        b = next;
        next = a + b;
    }

    printf("\n");
    return 0;
}
