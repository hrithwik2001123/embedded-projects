#include <stdio.h>
#include <stdlib.h>

int fibonacci(int a) {
    int first = 0, second = 1, sum = 0, i;

    if (a == 0) {
        return first;
    }

    for (i = 2; i <= a; i++) {
        sum = first + second;
        first = second;
        second = sum;
    }

}

int main() {
    int a;
    printf("Enter a number: ");
    scanf("%d", &a);

    int result = fibonacci(a);
    printf("Fibonacci number at position %d is %d\n", a, result);
    return 0;
}
