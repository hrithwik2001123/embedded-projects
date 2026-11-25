#include <stdio.h>
#include <stdlib.h>
int gra(int x )
{
    int clube;
   clube=x*x*x;
   printf("output = %d",clube);
}
int main()
{
     int x;
     printf("enter a  number ");
    scanf("%d",&x);
    gra(x);
    return 0;
}
