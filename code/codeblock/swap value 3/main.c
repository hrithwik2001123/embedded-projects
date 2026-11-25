#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a,b,c;
    printf("enter a two value ");
    scanf("%d%d",&a,&b);
    c=a;
    a=b;
    b=c;
    printf("the is swap %d %d",a,b);
    return 0;
}
