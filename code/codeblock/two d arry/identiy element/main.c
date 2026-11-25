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
            if(a[i][j]==1)
            {
               count++;
            }
            else if (a[i][j]==0)
            {
                co++;
            }
        }
    }
    if(count==r||count==c)
    {
      printf("entered the identity matrix");
    }
    else if (co==r||co==c)  {
        printf("enter the identity matrix");
    }
    else {
        printf("not a identity matrix");
    }
    return 0;
}
