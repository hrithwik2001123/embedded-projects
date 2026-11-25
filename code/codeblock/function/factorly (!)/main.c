#include <stdio.h>
#include <stdlib.h>
int factorly_1(int a)
{
    int i,b;
    b=1;
    for(i=1;i<=a;i++){
        b=b*i;
    }
    return b;
}
 int factorly(int a )
{
    int sum;
    for(int i=1;i<=a;i++)
    {
        int m=factorly_1(i);
        sum+=m/i;

    }
    return sum;
}
int main()
{ int a;
  printf("enter a number");
  scanf("%d",&a);
 int result= factorly(a);
 printf("%d",result);

    return 0;
}
