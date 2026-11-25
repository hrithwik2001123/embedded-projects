#include <stdio.h>
#include <stdlib.h>

int main()
{
    int p,n;
     printf("enter a number ");
    scanf("%d",&n);
    printf("enter a position \n");
    scanf("%d",&p);
   int x=((n>>p)&1);
    if (x==1)
    {
        printf(" the enter position is  set");
    }
    else
        {
            printf("enter a position is clear ");
        }
    return 0;
}
