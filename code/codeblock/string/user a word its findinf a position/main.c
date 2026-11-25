#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i;
    char a[50],b[20];
    printf("enter a word ");
    scanf("%[^\n]%*c",a);
    printf("enter a finding letter ");
    scanf("%s",b);
    for(i=0;a[i]!='\0';i++)
    {
        if(a[i] == b[0])
        {
            printf("%d position  %c",i,b[0]);
        }
    }

    return 0;
}
