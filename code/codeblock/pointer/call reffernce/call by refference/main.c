#include <stdio.h>
#include <stdlib.h>
int sum(int *a, int *b)
{
    *a=6,*b=3;
    printf("%d,%d\n",*a,*b);
}
int main()
{
    int a=10,b=4;
    sum(&a,&b);
    printf("%d,%d\n",a,b);
    return 0;
}
