#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n,i,j,max,min;
    printf("enter a limit");
    scanf("%d",&n);
    int arry[n];
    for(i=0;i<n;i++)
    {
        scanf("%d",&arry[i]);

    }
max=arry[0];
min=arry[n-1];
   for(i=0;i<n;i++)
   {
    if(max<arry[i])
    {
        max=arry[i];
    }

   }
   for(i=0;i<n;i++)
   {
    if(min>arry[i])
    {
        min=arry[i];
    }

   }

 printf("max=%d\n",max);
 printf("min=%d",min);
    return 0;
}
