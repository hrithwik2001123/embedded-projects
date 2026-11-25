#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a,i,rem,b=0;

    printf("enter a number to find the sum ");
    scanf("%d",&a);
    for(i=1;a>0;i++){
        rem=a%10;
        a=a/10;
        b=b+rem;
    }
    printf("%d\n",b);
    return 0;
}
