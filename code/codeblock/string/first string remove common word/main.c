#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i,j;
    char a[40];
    char b[40];
    printf("enter a word ");
    scanf("%s",a);
    printf("enter a word ");
     scanf("%s",b);
    for(i=0 ;a[i] != '\0' ;i++)
    {
        for(j=0 ;b[j] != '\0' ;j++)
        {
            if( a[i] == b[j] )
            {
              a[i] = '0';
               continue;
            }
        }

    }

    for(i=0 ;a[i] != '\0' ;i++)
    {
        if( a[i] != '0')
        {
         printf("%c",a[i]);
        }

    }
    return 0;
}
