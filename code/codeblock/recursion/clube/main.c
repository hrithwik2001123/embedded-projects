#include <stdio.h>
#include <stdlib.h>
int clube(int x ,int n)
{

    if(x<1)
        return 1;
    int m=n*clube(x-1,n);
    return m;
}
int main()
{
    int num,x=3,n;
    printf("enter a number\n ");
    scanf("%d",&n);
    int m=clube( x,n);
    printf("%d",m);
}
