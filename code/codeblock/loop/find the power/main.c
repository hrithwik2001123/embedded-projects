#include <stdio.h>
#include <stdlib.h>

int main()
{
    int b,i,e;
    float power=1;
    printf("enter number to find the power base and exponent ");
    scanf("%d",&b);
    scanf("%d",&e);
  for(i=1;i<=e;i++){
    power=power*b;
  }
    printf("%d^%d=%f",b,e,power);
    return 0;
}
