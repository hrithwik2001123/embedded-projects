#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i,n,j,count,k;
    count=0;
    printf("enter a limit");
    scanf("%d",&n);
    int arry[n];
    int array[n];
    for(i=0;i<n;i++)
    {
        scanf("%d",&arry[i]);

    }
   for(j=0;j<n;j++)
    {
        scanf("%d",&array[j]);

    }
     for(k=0;k<n;k++)
    {
    if(arry[k]==array[k])
    {
        count++;
    }

    }
    if(count==n){
        printf("equal");
    return 0;
}
else{
    printf("not equal ");
}
}
