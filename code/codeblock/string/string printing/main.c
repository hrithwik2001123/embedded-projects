#include <stdio.h>
#include <stdlib.h>

int main()
{
    char s[6];
    int i;
    printf("enter a character ");
    for(i=0;i!=6;i++)
    {
       scanf("%c",&s[i]);
    }
for(i=0;i!=6;i++)
{
 printf("%c",s[i]);
}

    return 0;
}
