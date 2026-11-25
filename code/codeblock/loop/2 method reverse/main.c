#include <stdio.h>
#include <stdlib.h>

int main()
{
     int a,rem,rev ;
    printf("enter a number ");
    scanf("%d",&a);
    while(a>0)
    {
        rem=a%10;
        a=a/10;
        rev=rev*10+rem;
    }
    printf("%d",rev);
    return 0;
}
