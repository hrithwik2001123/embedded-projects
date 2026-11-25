#include <stdio.h>
#include <stdlib.h>
int even(int n)
{
    if (n==1)
    {
        return;
    }
    even(n-1);
    if(n%2==0)
    {
        printf("%d\n",n);
    }

}
int main()
{
    int n;
    printf("enter a number \n");
    scanf("%d",&n);
    even(n);
    return 0;
}
