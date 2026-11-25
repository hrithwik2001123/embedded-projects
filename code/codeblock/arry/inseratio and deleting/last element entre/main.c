#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i,n,j,a;
    printf("enter a size ");
    scanf("%d",&n);
    int arry[n];
    for(i=0;i<n;i++)
    {
        scanf("%d,",&arry[i]);

    }
    printf("last element");
    scanf("%d",&a);
    arry[n]=a;
    for(j=0;j<=n;j++)
    {
        printf("%d",arry[j]);
    }
    return 0;
}
