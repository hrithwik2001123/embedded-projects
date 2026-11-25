#include <stdio.h>

// Function to print the binary representation of a number
void printBinary(int n) {
    // We will print the binary representation using 8 bits (for simplicity)
    for (int i = 7; i >= 0; i--) {
        int bit = (n >> i) & 1;  // Right shift and AND to get the bit at position i
        printf("%d", bit);
    }
    printf("\n");
}

int main() {
    int a = 5;  // 5 in binary: 00000101
    int b = 3;  // 3 in binary: 00000011

    // Bitwise AND
    int andResult = a & b;

    // Bitwise OR
    int orResult = a | b;

    // Bitwise XOR
    int xorResult = a ^ b;

    // Bitwise NOT (for a)
    int notResult = ~a;

    // Print the original numbers in binary
    printf("a in binary:  ");
    printBinary(a);

    printf("b in binary:  ");
    printBinary(b);

    // Print bitwise operation results in binary
    printf("Bitwise AND (a & b):  ");
    printBinary(andResult);

    printf("Bitwise OR (a | b):   ");
    printBinary(orResult);

    printf("Bitwise XOR (a ^ b):  ");
    printBinary(xorResult);

    printf("Bitwise NOT (~a):     ");
    printBinary(notResult);

    return 0;
}
