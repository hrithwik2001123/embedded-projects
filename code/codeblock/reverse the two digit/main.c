#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a,rev,rev1;
    printf("enter value is \n");
    scanf("%d",&a);
    rev=a/10;
    rev1=a%10;
    printf(" the value is %d%d",rev1,rev);
    return 0;
}
