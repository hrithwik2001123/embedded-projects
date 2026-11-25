#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i,j,n;
    printf("enter a limit");
    scanf("%d",&n);
    int arry[n];
    for(i=0;i<n;i++)
    {

        scanf("%d",&arry[i]);
    }
    for(j=n-1;j>=0;j--)
    {

      printf("%d ",arry[j]);
    }

    return 0;
}
