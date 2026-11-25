#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i, j;
    char arry[] = "hi world";
    char arry2[] = "hello";
    for(i = 3, j = 0; arry2[j] != '\0'; i++, j++)
    {
        arry[i] = arry2[j];
    }
    for(i = 0; arry[i] != '\0'; i++)
    {
        printf("%c", arry[i]);
    }

    return 0;
}
