#include <stdio.h>
#include <stdlib.h>

int main()
{
   short int a,b,sum;
    printf("enter two number ");
    scanf("%hd%hd",&a,&b);
    sum=a+b;
    printf("overflow");
    printf("sum=%hd",sum);
    return 0;
}
