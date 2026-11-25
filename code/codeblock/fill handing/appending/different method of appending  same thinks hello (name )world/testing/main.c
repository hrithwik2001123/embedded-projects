#include <stdio.h>
#include <string.h>

int main()
{
    FILE *fptr = NULL;
    fptr = fopen("abc3.text", "w");
    if (fptr == NULL)
    {
        printf("Error .\n");
        return 1;
    }
    fputs("hello world", fptr);
    fclose(fptr);
    fptr = fopen("abc3.text", "r");
    if (fptr == NULL)
    {
        printf("Error 1 .\n");
        return 1;
    }

    char ch[100];
    fgets(ch, 100, fptr);
    fclose(fptr);
    int i;
    for (i = 0; ch[i] != '\0'; i++)
    {
        if (ch[i] == ' ')
        {
            int len = strlen(ch);
            for (int j = len; j > i; j--)
            {
                ch[j + 9] = ch[j];
            }


            for (int j = 1; j <= 9; j++)
            {
                ch[i + j] = ' ';
            }

            break;
        }
    }
    fptr = fopen("abc3.text", "w");
    if (fptr == NULL)
    {
        printf("Error 3.\n");
        return 1;
    }

    fputs(ch, fptr);
    fseek(fptr, 6, SEEK_SET);
    fputs("Hrithwik ", fptr);
    fclose(fptr);

    return 0;
}
