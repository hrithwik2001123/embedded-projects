#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a,b,c;
    printf("enter a two value ");
    scanf("%d%d",&a,&b);
   a=a+b;
   b=a-b;
   a=a-b;
    printf("enter the value %d\n%d",a,b);
    return 0;
}
