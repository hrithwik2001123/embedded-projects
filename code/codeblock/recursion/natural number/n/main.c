#include <stdio.h>
#include <stdlib.h>
int natural(int n)
{
    if(n<1)
    {
        return ;
    }
  natural(n-1);
  printf("%d,",n);
}
int main()
{

    int n, k=1;
    printf("enter a limit \n");
    scanf("%d",&n);
    natural(n);
}
