#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a, i, sum;
    sum = 0;
    printf("Enter a number: ");
    scanf("%d", &a);
    while(i <= a)
    {
        sum += i;
        i++;
    }
    printf("The sum %d ",  sum);
    return 0;
}
