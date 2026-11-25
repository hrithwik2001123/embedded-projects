#include <stdio.h>
#include <math.h>

// Optimized function to check if a number is prime
int is_prime(int a) {
    if (a <= 1) return 0;  // 0 and 1 are not prime numbers
    if (a == 2) return 1;  // 2 is a prime number
    if (a % 2 == 0) return 0;  // Even numbers greater than 2 are not prime

    int sqrt_a = (int)sqrt(a);
    for (int i = 3; i <= sqrt_a; i += 2) {
        if (a % i == 0) {
            return 0;  // Not a prime number
        }
    }
    return 1;  // Prime number
}

// Function to find pairs of prime numbers that sum up to 'a'
void find_prime_pairs(int a) {
    for (int i = 2; i <= a / 2; i++) {
        int j = a - i;
        if (is_prime(i) && is_prime(j)) {
            printf("%d = %d + %d\n", a, i, j);
        }
    }
}

int main() {
    int a;
    printf("Enter a number: ");
    scanf("%d", &a);

    // Check if the number is prime
    if (is_prime(a)) {
        printf("The number %d is prime.\n", a);
    } else {
        printf("The number %d is not prime.\n", a);
    }

    // Find and print prime pairs that sum up to the input number
    printf("Prime pairs that sum up to %d are:\n", a);
    find_prime_pairs(a);

    return 0;
}
