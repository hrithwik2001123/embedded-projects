#include <stdio.h>

// Function to print the binary representation of a number
void printBinary(int num) {
    int bits = sizeof(int) * 8; // Get the number of bits in an int (usually 32 bits)

    for (int i = bits - 1; i >= 0; i--) {
        int bit = (num >> i) & 1; // Extract the i-th bit from the number
        printf("%d", bit);
    }
    printf("\n"); // Move to the next line after printing the binary number
}

int main() {
    int a = 5;
    int leftShift1 = a << 1;
    int leftShift2 = a << 5;
    int rightShift1 = a >> 1;
    int rightShift2 = a >> 2;

    printf("Original number: %d\n", a);
    printf("Left shift by 1: %d\n", leftShift1);
    printf("Left shift by 5: %d\n", leftShift2);
    printf("Right shift by 3: %d\n", rightShift1);

    // Print the binary representation of rightShift1
    printf("Binary of Right shift by 1: ");
    printBinary(rightShift1);

    printf("Right shift by 2: %d\n", rightShift2);
  printBinary(rightShift2);
    return 0;
}
