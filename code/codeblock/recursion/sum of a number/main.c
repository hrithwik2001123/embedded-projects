#include <stdio.h>
#include <stdlib.h>
int sum(int n)
{
    if(n==0)
    return 0;
    int m=n+sum(n-1);
    return m;

}
int main()
{
    int n;
    printf("enter a number ");
    scanf("%d",&n);
    int m=sum(n);
    printf("%d\n",m);
    return 0;
}
