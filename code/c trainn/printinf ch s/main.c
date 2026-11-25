#include <stdio.h>

int main()
{
    char ch;
    char s[100], sen[100];

    // Take inputs
    scanf("%c", &ch);            // To take the character input
    scanf("\n");                  // To consume the newline after the first character input
    gets(s);                      // To take the string input
    gets(sen);                    // To take the sentence input

    // Print the outputs
    printf("%c\n", ch);           // Print the character
    printf("%s\n", s);            // Print the string
    printf("%s\n", sen);          // Print the sentence

    return 0;
}
