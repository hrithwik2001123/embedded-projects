#include <stdio.h>
#include <stdlib.h>
int sum(int a , int b)
{
    a=2;
    b=3;
    printf("%d,%d\n",a,b);
}
int main()
{
    int a=10,b=5;
    sum(a,b);
    printf("%d,%d\n",a,b);
    return 0;
}
