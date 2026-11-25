#include <stdio.h>
#include <stdlib.h>

int main()
{
    int p,n,count;
     printf("enter a number ");
    scanf("%d",&n);
   for( int i=0;i<=n;i++){
   int x=((n>>i)&1);
    if (x==1)
    {
        count++;
    }
   }
   printf("%d",count);
    return 0;
}
