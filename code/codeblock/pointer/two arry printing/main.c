#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i,j,r,c;
    printf("enter a how many row you need ");
    scanf("%d",&r);
    printf("enter a how many colum you need ");
     scanf("%d",&c);
     int arry[r][c];
    for(i=0;i<r;i++)
    {
        for(j=0;j<c;j++)
        {
            scanf("%d",&arry[i][j]);
        }
    }

    for(i=0;i<r;i++)
    {
        for(j=0;j<c;j++)
        {
            printf("%d\t",*(*(arry+i)+j));
        }
        printf("\n");
    }
}
