#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n,i,p,v;
    printf("enter a limit");
    scanf("%d",&n);
    int arry[n];
    for(i=0;i<n;i++)
    {
        scanf("%d",&arry[i]);

    }
    printf("enter a value you need to remove ");
    scanf("%d",&p);
    for(i=p-1;i<n;i++)
    {
        arry[i]=arry[i+1];
    }
    for(i=0;i<n-1;i++)
    {
        printf("%d",arry[i]);
    }

    return 0;
}
