#include <stdio.h>
#include <stdlib.h>
int factorial(int num)
{
  int n=0;
    if (num==0)

             return 1 ;


       return(num*factorial(num-1));
}



int main()
{
    int number;
    printf("enter a number \n");
    scanf("%d",&number);
    int num =factorial(number);
    printf("%d this the factorial ",num);
    return 0;
}
