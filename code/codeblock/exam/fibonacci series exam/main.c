#include <stdio.h>
#include <stdlib.h>
int fibonacci(int a)
{
    int  sum=0, second=1,first=0,i;
    for(i=1;i<=a;i++)
    {
     printf("%d,",first);
        sum=first+second;
        first=second;
        second=sum;
    }
}
int main()
{ int a;
    printf("enter a number ");
    scanf("%d",&a);
    fibonacci(a);
    return 0;
}
