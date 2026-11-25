#include <stdio.h>
#include <stdlib.h>
int even(int n)
{
    if (n<1)
    {
        return;
    }
        printf("%d\n",n);
        even(n-1);

}
int main()
{
    int n;
    printf("enter a number \n");
    scanf("%d",&n);
    even(n);
    return 0;
}
