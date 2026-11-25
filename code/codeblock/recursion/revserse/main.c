#include <stdio.h>
#include <stdlib.h>
int revs (int a, int rev)
{
    if(a==0)
    {
        return rev ;
    }
    int  rem=a%10;
        rev=rev*10+rem;
      revs(a/10,rev);
}
int main()
{
    int a;
    printf("enter a number \n");
    scanf("%d",&a);
    int n=revs(a,0);
    printf("%d",n);
}
