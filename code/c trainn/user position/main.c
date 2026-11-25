#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i,j,n,p,v;
    printf("enter a limit");
    scanf("%d",&n);
    int arry[n];
    for(i=0;i<n;i++)
    {
        scanf("%d",&arry[i]);
    }
    printf("enter a position and value");
    scanf("%d%d",&p,&v);
    for(i=n-1;i>=p-1;i--)
    {
        arry[i+1]=arry[i];
    }
    arry[p-1]=v;
    for(i=0;i<=n;i++){
    printf("%d\n",arry[i]);
    }
    return 0;
}
