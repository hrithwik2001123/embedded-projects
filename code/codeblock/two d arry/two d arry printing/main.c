#include <stdio.h>
#include <stdlib.h>

int main()
{
    int r,c,i,j;
    printf("enter row ");
    scanf("%d",&r);
    printf("enter column");
    scanf("%d",&c);
    int a[r][c];
    printf("enter the numbers");
    for(i=0;i<r;i++)
    {
        for(j=0;j<c;j++)
        {
            scanf("%d",&a[i][j]);
        }
    }
    for(i=0;i<r;i++)
    {
        for(j=0;j<c;j++)
        {
            printf("%d",a[i][j]);

        }
        printf("\n");
    }
    return 0;
}
