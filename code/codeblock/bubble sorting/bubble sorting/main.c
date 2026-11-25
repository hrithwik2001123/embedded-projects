#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i,j,n,t;
    printf("enter a limit ");
    scanf("%d",&n);
    int arry[n];
    for(i=0;i<n;i++)
        {
            scanf("%d",&arry[i]);
        }
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(arry[j]>arry[j+1])
            {
                t=arry[j];
                arry[j]=arry[j+1];
                arry[j+1]=t;
            }
        }
    }
    for(i=0;i<n;i++)
    {
        printf("%d,",arry[i]);
    }

    return 0;
}
