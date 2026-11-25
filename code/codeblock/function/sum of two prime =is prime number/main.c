#include <stdio.h>
#include <stdlib.h>

int is_prime(int num) {
    if (num < 2)
        return 0;
    for (int i = 2; i <= num / 2; i++) {
        if (num % i == 0)
            return 0;
    }
    return 1;
}

void prime_sum(int a) {
    int flag= 0;
    for (int i = 2; i <= a ; i++) {
       for(int j=2;j<=a;j++) {
        if (is_prime(i) && is_prime(j)) {
                if(a==i+j){
            printf("%d = %d + %d\n", a, i, j);
            flag = 1;
            break;
                }
        }
       }
    }
    if (flag!=1) {
        printf("It's not possible to express %d as a sum of two prime numbers.\n", a);
    }
}

int main() {
    int a;
    printf("Enter a number: ");
    scanf("%d", &a);

    if (is_prime(a)) {
        printf("%d is a prime number.\n", a);
        prime_sum(a);
    } else if (a == 2) {
        printf("2 = 1 + 1\nBut 1 is not a prime number.\n");
    } else {
        printf("%d is not a prime number.\n", a);
        prime_sum(a);
    }

    return 0;
}
