#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a,i ;
    i=0;
    printf("enter a number ");
    scanf("%d",&a);
    while(a>0)
    {
      a=a%10;
      i--;
    }
    printf("%d the digits is ",i);
    return 0;
}
