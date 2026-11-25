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
    for(i=0;i<n-1;i++)
    {
        arry[i]=arry[i+1];
    }
    for(i=0;i<n-1;i++){
    printf("%d\n",arry[i]);
    }
    return 0;
}
