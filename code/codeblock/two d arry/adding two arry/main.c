#include <stdio.h>
#include <stdlib.h>

int main()
{
    int r,c,i,j,sum=0,k,o;
    printf("enter row ");
    scanf("%d",&r);
    printf("enter column");
    scanf("%d",&c);
    int a[r][c];
    int a1[r][c];
    printf("enter the numbers");
    for(i=0;i<r;i++)
    {
        for(j=0;j<c;j++)
        {
            scanf("%d",&a[i][j]);
        }
    }
    printf("second arry");
    for(i=0;i<r;i++)
    {
        for(j=0;j<c;j++)
        {
            scanf("%d",&a1[i][j]);

        }

    }
    for(i=0;i<r;i++)
    {
        for(j=0;j<c;j++)
        {
            //printf("%d",a[i][j]);

        }
        printf("\n");
    }
     for(i=0;i<r;i++)
    {
        for(j=0;j<c;j++)
        {
          //  printf("%d",a[i][j]);

        }
        printf("\n");
    }

    for(i=0;i<r;i++)
    {
        for(j=0;j<c;j++)
        {
            sum=a[i][j]+a1[i][j];
            printf("%d",sum);
        }
        printf("\n");

    }


    return 0;


}
