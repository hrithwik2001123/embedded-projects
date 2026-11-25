#include <stdio.h>
#include <stdlib.h>

int main()
{
    int count,i;
    long int sum=0,first=9;
    printf("enter a the count ");
    scanf("%ld",&count);
    for(i=1;i<=count;i++)
    {

        sum+=first;
        first=first*10+9;
        printf("%d\n",first);
    }
    printf("sun=%ld",sum);
    return 0;
}
