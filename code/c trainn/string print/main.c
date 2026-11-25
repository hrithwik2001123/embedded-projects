#include <stdio.h>
#include <stdlib.h>

int main() {
    char character;
    char string[100];
    char sentence[100];

    printf("Enter a character: ");
    scanf("%c", &character);
    getchar();

    printf("Enter a string: ");
    scanf("%[^\n]%*c", string);


    printf("Enter a sentence: ");
    scanf("%[^\n]%*c", sentence);


    printf("%c\n", character);
    printf("%s\n", string);
    printf("%s\n", sentence);

    return 0;
}
