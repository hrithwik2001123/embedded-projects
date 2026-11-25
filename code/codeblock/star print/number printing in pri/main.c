#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a,i,j;
    printf("enter a nnumber line ");
    scanf("%d",&a);
    for(i=1;i<=a;i++)
    {
        for(j=1;j<=i;j++)
        {
            printf("%d",j);
        }
         printf("\n");
    }

    return 0;
}
