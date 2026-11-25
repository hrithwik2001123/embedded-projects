#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i,n,j,a;
    printf("enter a size ");
    scanf("%d",&n);
    int arry[n+1];
    for(i=0;i<n;i++)
    {
        scanf("%d,",&arry[i]);

    }
    for(i=n-1;i>=0;i--)
    {
        arry[i+1]=arry[i];

    }
    printf("insertion element");
    scanf("%d",&a);
    arry[0]=a;
    for(j=0;j<=n;j++)
    {
        printf("%d",arry[j]);
    }
    return 0;
}
