   #include <stdio.h>
#include <stdlib.h>

int main()
{
    int r,c,i,j,count=0,co=0;
   printf("enter number r");
    scanf("%d",&r);
    printf("enter number c");
    scanf("%d",&c);
    int a[r][c];
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
    printf("\n");
    for(i=0;i<r;i++)
    {
        for(j=0;j<c;j++)
        {
            printf("%d",a[j][i]);
        }
        printf("\n");
    }
}
