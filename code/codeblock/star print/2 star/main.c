#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i,a,j;
    printf("how much star you want");
    scanf("%d",&a);
    for (i=0;i<a;i++)
    {
        for(j=0;j<a;j++)
        {
            printf(" * ");
        }
        printf("\n");
    }
    return 0;
}
