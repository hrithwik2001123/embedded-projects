#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a,b,sum,s;
    printf("enter a two angles ");
    scanf("%d%d",&a,&b);
    s=a+b;
    sum=180-s;
    printf("3 side of triangle %d",sum);
    return 0;
}
