#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i,j,n,tem=0,max;
    printf("enter the limit ");
    scanf("%d",&n);
    int arry[n];
     int*ptr=arry;
     for(i=0;i<n;i++)
     {
         scanf("%d",(ptr+i));
     }
     printf("before sorting\n");
     for(i=0;i<n;i++)
     {
         printf("%d,",*(ptr+i));
     }
     printf("\n after the sorting");
     for(i=0;i<n-1;i++)
     {
         max=i;
         for(j=i+1;j<n;j++)
         {

            if(*(ptr+max)<*(ptr+j))
            {
                max=j;
            }
         }
         if(max!=i)
         {
             tem=*(ptr+i);
             *(ptr+i)=*(ptr+max);
             *(ptr+max)=tem;
         }
     }
     for(i=0;i<n;i++)
     {
         printf("%d,",*(ptr+i));
     }
}
