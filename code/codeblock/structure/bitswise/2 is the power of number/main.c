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
  if(count==1)
  {
      printf("its a power of 2");
  }
  else
  {
      printf("its not a power of 2");
  }
    return 0;
}
