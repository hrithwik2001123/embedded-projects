#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i,j,n,t=0,min;
    printf("enter a limit ");
    scanf("%d",&n);
    int arry[n];
    for(i=0;i<n;i++)
    {

        scanf("%d",&arry[i]);

    }
    for(i=0;i<n;i++)
    {
        min=i;
        for(j=i+1;j<n;j++)
        {
            if(arry[min]>arry[j])
            {
                min=j;
            }
        }
        if(min!=i)
        {
            t=arry[i];
            arry[i]=arry[min];
            arry[min]=t;
        }
    }

   for(i=0;i<n;i++)
   {
       printf("%d,",arry[i]);
   }
    return 0;
}
