#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    printf("enter a number ");
    scanf("%d",&n);
    if((n&1)==1)
    {
        printf("enter a is odd");
    }
    else
        {
            printf("enter a is even ");
        }
    return 0;
}
