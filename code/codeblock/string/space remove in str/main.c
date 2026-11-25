#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i,j;
    char b[40];
    printf("enter a word ");
     scanf("%[^\n]%*c",b);

    for(i=0 ;b[i] != '\0' ;i++)
    {
        if( b[i] != ' ')
        {
         printf("%c",b[i]);
        }

    }
    return 0;
}
