#include <stdio.h>
#include <string.h>

int main() {
    int i = 0, j = 0;
    char a[100], b[100], c[100], d[100];

    printf("Enter a sentence: ");
    scanf("%[^\n]%*c", a);
    printf("Enter a word to replace: ");
    scanf("%[^\n]%*c", b);
    printf("Enter the new word: ");
    scanf("%[^\n]%*c", c);

    while (1) {
        if (a[i] != ' ' && a[i] != '\0') {
            d[j++] = a[i]; // Collect current word
        } else {
            d[j] = '\0'; // Null-terminate the current word

            if (strcmp(b, d) == 0) {
                printf("%s", c); // Replace the word
            } else {
                printf("%s", d); // Print the original word
            }

            if (a[i] == '\0') break; // End of sentence

            printf(" "); // Add space between words
            j = 0; // Reset word builder index
        }
        i++;
    }
    return 0;
}
