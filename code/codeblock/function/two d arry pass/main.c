#include <stdio.h>
#include <stdlib.h>
int ary (int r ,int c, int arry[r][c])
{
    //arry[r][c];

        for( int i=0;i<r;i++)
    {
        for( int j=0;j<c;j++)
        {
            printf("%d\t",arry[i][j]);
        }
        printf("\n");
}
}
int main()
{
    int r,c,i,j;
    int arry[3][3];
    printf("enter number of row");
    scanf("%d",&r);
    printf("enter number of colum");
    scanf("%d",&c);
    for(int i=0;i<r;i++)
    {
        for(int j=0;j<c;j++)
        {
            scanf("%d",&arry[i][j]);
        }
    }
    printf("first arry\n");
    ary(r,c,arry);
    }
