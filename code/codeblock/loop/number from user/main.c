#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a ,count;
    count=0;
    printf("enter a number ");
    scanf("%d",&a);
    while(a>0)
    {
      a=a/10;
      count++;
    }
    printf("%d the digits is ",count);
    return 0;
}
