#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a,b,c,var;
    printf("enter to number ");
    scanf("%d%d%d",&a,&b,&c);
   var=(a>b)?((a>c)?a:c ):((b>c)?b:c);
    printf("%d is greater",var);
    return 0;
}
