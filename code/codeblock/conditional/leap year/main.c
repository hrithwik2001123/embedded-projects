#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a;
    printf("enter a number year");
    scanf("%d",&a);
    (a%4==0)?printf("you entered the leap year %d",a):printf("its not leap year %d",a);
    return 0;
}
