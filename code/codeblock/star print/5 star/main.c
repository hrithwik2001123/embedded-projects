#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i,a,j,sp;
    printf("how much star you want");
    scanf("%d",&a);
    for (i=0;i<a;i++)
    {
        for(sp=0;sp<i;sp++)
        {
            printf(" ");
        }
        for(j=a;j>i;j--)
        {
          printf("*");
        }
        printf("\n");
    }
    return 0;
}
