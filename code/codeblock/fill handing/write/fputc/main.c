#include <stdio.h>

int main()
{
    FILE *fptr = NULL;
    fptr = fopen("D:/codeblock/fill handing/writ/enew.txt", "w"); // Corrected filename
    char ch = 'c';

    if (fptr == NULL)
    {
        printf("Error opening file\n");
        return 1; // Return an error code
    }

    fputc(ch, fptr);
    fclose(fptr);

    printf("Character written to file successfully\n");

    return 0;
}
