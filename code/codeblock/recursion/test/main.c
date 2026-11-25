#include <stdio.h>

int reverse(int a, int rev) {
    if (a == 0) {
        return ;
    }
    int rem = a % 10;
    rev = rev * 10 + rem;
    return reverse(a / 10, rev);
}

void palindrome(int a) {
    if (a < 0) {
        printf("Negative numbers are not palindromes.\n");
        return;
    }

    int rev = reverse(a, 0);
    printf("Reversed number: %d\n", rev);

    if (rev == a) {
        printf("The number is a palindrome.\n");
    } else {
        printf("The number is not a palindrome.\n");
    }
}

int main() {
    int a;
    printf("Enter a number: ");
    scanf("%d", &a);

    palindrome(a);

    return 0;
}
