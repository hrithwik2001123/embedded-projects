#include <stdio.h>
#include <string.h>

int main() {
     FILE *fptr = NULL;
    fptr = fopen("string.txt", "w");
    if (fptr == NULL)
    {
        printf("Error .\n");
        return 1;
    }
    fputs("hi hello my name is hrithwik", fptr);
    fclose(fptr);
  fptr = fopen("string.txt", "r");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    char fileContent[200];
    fgets(fileContent, 200, fptr);

    char searchString[50];
    printf("Enter the word to search: ");
    scanf("%s", searchString);
    char word[50];
    int i = 0, j = 0, found = 0;
    for (i = 0; fileContent[i] != '\0'; i++) {
        if (fileContent[i] == ' ' || fileContent[i] == '\n') {
            word[j] = '\0';
            j = 0;
            if (strcmp(word, searchString) == 0) {
                found = 1;
                break;
            }
        } else {
            word[j++] = fileContent[i];
        }
    }


   // if (strcmp(word, searchString) == 0) {
       // found = 1;
   // }

    if (found) {
        printf("Word '%s' found in the string.\n", searchString);
    } else {
        printf("Word '%s' not found in the string.\n", searchString);
    }

    return 0;
}
