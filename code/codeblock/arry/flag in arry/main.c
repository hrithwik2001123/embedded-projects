#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i,j,k,n,flag;
    flag=0;
    printf("enter a size");
    scanf("%d",&n);
    int arry[n];
    int array[n];
    printf("enter a limit1");
    for(i=0;i<n;i++)
    {
        scanf("%d",&arry[i]);

    }
    printf("enter a limit2");
    for(i=0;i<n;i++)
    {
        scanf("%d",&array[i]);
    }
    for(i=0;i<n;i++)
    {
        if(arry[i]!=array[i])
        {
            flag=1;
            break;
        }
    }
    if(flag==1)
    {
        printf("its not equal");
    }
    else{
        printf("its equal ");

    }
    return 0;
}
