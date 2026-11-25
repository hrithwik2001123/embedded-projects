#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a;
    printf("enter a number");
    scanf("%d",&a);
    (a%2==0)?printf(" %d its even",a):printf(" %d is odd",a);
}
