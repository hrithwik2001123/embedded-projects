#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fptr = NULL;
    fptr = fopen("hello.txt", "w");

    if (fptr == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    fputs("hello          world ", fptr);

    fseek(fptr, 6, SEEK_SET);


    fputs("Hrithwik ", fptr);

    fclose(fptr);
    return 0;
}
